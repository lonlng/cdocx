/// @file system/details/for_each_member_visitor.h
#pragma once

#include <list>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>
#include <system/details/delegate_holding_variables.h>
#include <system/details/held_variables.h>
#include <system/object.h>
#include <system/iobjects_holder.h>

#ifdef __DBG_FOR_EACH_MEMBER
namespace System { namespace DBG
{
    /// Visitor to collect information on shared pointers owned by objects for loop detection purposes.
    /// Used by FOR_EACH_MEMBER mechanism.
    struct for_each_member_visitor
    {
        /// Information on single node (object) in ownership graph.
        struct node_info
        {
            /// Unique identifier of node.
            const int id;
            /// Class Name.
            const std::string class_name;
            /// Member name.
            std::string member_name;
            /// List of strings.
            typedef std::vector<std::string> v_string_t;
            /// List of member reference names.
            v_string_t ref_members_name;
            /// Is shard flag.
            bool is_shared;
            /// aliased id's.
            const std::vector<int> alias_ids;

            /// Creates information structure.
            /// @param _id Node identifier, should be unique.
            node_info(int _id) : id(_id), is_shared(true) {}
            /// Creates information structure.
            /// @param _id Node identifier, should be unique.
            /// @param _is_shared Shared flag
            /// @param _class_name Node class name.
            node_info(int _id, bool _is_shared, const char *_class_name) : id(_id), is_shared(_is_shared), class_name(_class_name) {}
            /// Creates information structure.
            /// @param _id Node identifier, should be unique.
            /// @param _is_shared Shared flag
            /// @param _class_name Node class name.
            /// @param _member_name Node member name.
            node_info(int _id, bool _is_shared, const std::vector<int> & _alias_id, const char *_class_name, const char *_member_name) : id(_id), is_shared(_is_shared), alias_ids(std::move(_alias_id)), class_name(_class_name), member_name(_member_name) {}

            /// Allows record ordering by id.
            /// @param nfo RHS operand.
            /// @return True if this preceeds @p nfo, false otherwise.
            bool operator < (const node_info &nfo) const { return id < nfo.id; }
        };

        /// Node information with additional information on ids of objects having back references into current one.
        struct node_info_ex : node_info
        {
            /// Creates information structure.
            /// @param _id Node identifier, should be unique.
            node_info_ex(int _id) : node_info(_id) {}
            /// Creates information structure.
            /// @param _id Node identifier, should be unique.
            /// @param _is_shared Shared flag
            /// @param _class_name Node class name.
            node_info_ex(int _id, bool _is_shared, const char *_class_name) : node_info(_id, _is_shared, _class_name) {}

            /// Set of node identifiers.
            typedef std::set<int> set_i_t;
            /// Ids of nodes referencing back into current one.
            set_i_t back_references;

            /// Checks if other nodes reference current one.
            /// @return True if one or more references to current node is known about, false otherwise.
            bool has_reference() const { return !back_references.empty(); }
        };

        /// Information on multiple nodes.
        typedef std::set<node_info> set_ids;
        /// Maps extended node information to information on multiple nodes.
        typedef std::map<node_info_ex, set_ids> map_id_ref_to_ids;

        /// Holds information on relations between nodes.
        map_id_ref_to_ids relations;

        /// Adds information on node on which DBG_for_each_member method was called.
        /// @param owner Object to capture information for.
        void add_self(const Object *owner)
        {
            CODEPORTING_DEBUG_ASSERT(owner);
            relations.insert(map_id_ref_to_ids::value_type(node_info_ex(System::Details::DbgTools::DBG_InstanceNo(owner), true, owner->DBG_class_name()), set_ids()));
        }

        template <typename T>
        typename std::enable_if<!IsSmartPtr<T>::value && !std::is_base_of<Details::DelegateHoldingVariables, T>::value && !std::is_base_of<System::Object, T>::value, void>::type
            add_member(const Object *owner, const T& member, const char *member_name)
        {}

        /// Dummy to skip information on non-pointer objects.
        /// @param owner Owner object.
        /// @param member Non-pointer member to skip.
        /// @param member_name Member name.
        template <typename T>
        typename std::enable_if<!IsSmartPtr<T>::value && !std::is_base_of<Details::DelegateHoldingVariables, T>::value && std::is_base_of<System::Object, T>::value, void>::type
            add_member(const Object *owner, const T& member, const char *member_name)
        {
            CODEPORTING_DEBUG_ASSERT(owner);
            map_id_ref_to_ids::iterator it = relations.find(node_info_ex(System::Details::DbgTools::DBG_InstanceNo(owner)));
            CODEPORTING_DEBUG_ASSERT(relations.end() != it);

            std::vector<int> alias_ids;
            it->second.insert(node_info(System::Details::DbgTools::DBG_InstanceNo(&member), true, alias_ids, static_cast<const System::Object*>(&member)->DBG_class_name(), member_name));

            if (relations.end() == relations.find(System::Details::DbgTools::DBG_InstanceNo(&member))) {
                static_cast<const System::Object*>(&member)->DBG_for_each_member(*this);
            }
        }

        /// Adds information on member shared pointer.
        /// @param owner Owner object.
        /// @param member Pointer member to add.
        /// @param member_name Member name.
        template <typename T>
        typename std::enable_if<IsSmartPtr<T>::value, void>::type add_member(const Object *owner, const T& member, const char *member_name)
        {
            CODEPORTING_DEBUG_ASSERT(owner);
            map_id_ref_to_ids::iterator it = relations.find(node_info_ex(System::Details::DbgTools::DBG_InstanceNo(owner)));
            CODEPORTING_DEBUG_ASSERT(relations.end() != it);

            const Object *_member = (const Object*)member.GetObjectOrNull();

            if (_member)
            {
                std::vector<int> alias_ids;

#if !defined(ENABLE_EXTERNAL_REFCOUNT)
                if (member.IsAliasingPtr())
                {
                    auto owned = member.GetObjectOwner();
                    auto * holder = dynamic_cast<CodePorting::Translator::Cs2Cpp::Details::IObjectsHolder*>(owned);
                    if (holder)
                    {
                        alias_ids = holder->getHoldObjectIds();
                    }
                    else
                    {
                        alias_ids.push_back(System::Details::DbgTools::DBG_InstanceNo(owned));
                    }                    
                }
#endif

                it->second.insert(node_info(System::Details::DbgTools::DBG_InstanceNo(_member), member.IsShared(), alias_ids, _member->DBG_class_name(), member_name));

                if (relations.end() == relations.find(System::Details::DbgTools::DBG_InstanceNo(_member))) {
                    _member->DBG_for_each_member(*this);
                }
            }
        }

        /// Adds information on delegate member.
        /// @param owner Owner object.
        /// @param member Delegate member to add.
        /// @param member_name Member name.
        template <typename T>
        typename std::enable_if<!IsSmartPtr<T>::value && std::is_base_of<Details::DelegateHoldingVariables, T>::value, void>::type
            add_member(const Object* owner, const T &member, const char* member_name)
        {
            add_held_variables(owner, member.GetHeldVariables(), member_name);
        }

        /// Adds information on template member. Uses SFINAE to call pointer or non-pointer version.
        /// @param owner Owner object.
        /// @param member Member to add or to skip.
        /// @param member_name Member name.
        template<typename T>
        inline void add_template_member(const Object *owner, const T *member, const char *member_name)
        {
            _add_template_member(owner, member, member_name);
        }

        /// Fills information on back references (which object is referenced by which) as an opposite to forward references
        /// being added by add_* methods (which object references which).
        void build_back_references(bool include_weak = true)
        {
            for(map_id_ref_to_ids::value_type &vt : relations)
            {
                for (const node_info &ni : vt.second)
                {
                    if (!include_weak && !ni.is_shared)
                        continue;
                    map_id_ref_to_ids::iterator it = relations.find(ni.id);
                    if (relations.end() != it) {
                        const_cast<node_info_ex*>(&(*it).first)->back_references.insert(vt.first.id);
                        const_cast<node_info_ex*>(&(*it).first)->ref_members_name.push_back(ni.member_name);
                    }
                }
            }
        }

    private:
        /// Adds information on member shared pointer.
        /// @param owner Owner object.
        /// @param member Pointer member to add.
        /// @param member_name Member name.
        template<typename T>
        inline typename std::enable_if<System::IsSmartPtr<T>::value, void>::type
            _add_template_member(const Object *owner, const T *member, const char *member_name)
        {
            add_member(owner, const_cast<T&>(*member), member_name);
        }

        /// Dummy to skip information on non-pointer objects.
        /// @param owner Owner object.
        /// @param member Non-pointer member to skip.
        /// @param member_name Member name.
        template<typename T>
        inline typename std::enable_if<!System::IsSmartPtr<T>::value, void>::type
            _add_template_member(const Object *owner, const T *member, const char *member_name)
        {
            //nothing to do...
        }

        /// Adds information about variables held by a delegate.
        /// @param owner Owner object.
        /// @param heldVariables A pointer to the collections of variables held by a delegate.
        /// @param member_name Member name.
        void add_held_variables(const Object* owner, const std::shared_ptr<Details::HeldVariables> &heldVariables, const char* member_name)
        {
            static const std::string delimiter("::");

            if (heldVariables)
            {
                const std::string prefix(member_name);

                for (const auto& sharedPointer: heldVariables->sharedPointers)
                {
                    auto fullName = std::make_shared<std::string>(prefix + delimiter + std::string(sharedPointer.first));
                    add_member(owner, MakeSharedPtr(sharedPointer.second.getObject()), fullName->c_str());
                    m_delegateCaptures.push_back(fullName);
                }

                for (const auto& value: heldVariables->values)
                {
                    auto fullName = std::make_shared<std::string>(prefix + delimiter + std::string(value.first));
                    add_member(owner, value.second, fullName->c_str());
                    m_delegateCaptures.push_back(fullName);
                }
            }
        }

        /// List of variables held by a delegate
        /// @remarks shared_ptr is used to avoid copying of strings when adding strings to a container or when copying
        /// the for_each_member_visitor structure. It helps to avoid creating of dangling pointers when
        /// calling add_member(owner, value.second, fullName->c_str()).
        std::list<std::shared_ptr<std::string>> m_delegateCaptures;
    };


    /// Checks if speific type is a specialiazation of std::pair used by STL map-like containers; inherits either std::false_type or std::true_type, depending on check result.
    /// @tparam T Type to check.
    /// @tparam U Formal argument for SFINAE to work.
    template<typename T, typename U = void>
    struct is_maped_type : std::false_type {};

    /// Specialization for std::pair.
    template<typename T>
    struct is_maped_type<T, typename std::enable_if<std::is_same<typename T::value_type, std::pair<const typename T::key_type, typename T::mapped_type> >::value >::type > : std::true_type {};

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for flat (non-mapped) collections of non-pointers and skips them.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<!System::IsSmartPtr<typename collectionT::value_type>::value && !is_maped_type<collectionT>::value && std::is_base_of<System::Object, typename collectionT::value_type>::value, void>::type
        for_each_of_Object(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        for (const auto& e : c) {
            visitor.add_member(owner, e, "[]");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for flat (non-mapped) collections of non-pointers and skips them.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<!System::IsSmartPtr<typename collectionT::value_type>::value && !is_maped_type<collectionT>::value && !std::is_base_of<System::Object, typename collectionT::value_type>::value, void>::type
        for_each_of_Object(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //nothing to do...
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections of non-pointers and skips them.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<
        !System::IsSmartPtr<typename collectionT::key_type>::value
        && !System::IsSmartPtr<typename collectionT::mapped_type>::value
        && !std::is_base_of<System::Object, typename collectionT::mapped_type>::value, void>::type
        for_each_of_Object_mapped_type(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //nothing to do...
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections of non-pointers and skips them.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<!System::IsSmartPtr<typename collectionT::key_type>::value
        && !System::IsSmartPtr<typename collectionT::mapped_type>::value
        && std::is_base_of<System::Object, typename collectionT::mapped_type>::value, void>::type
        for_each_of_Object_mapped_type(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //case m
        for (const typename collectionT::value_type& m : c) {
            visitor.add_member(owner, m.second, "-m");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections where both keys and values are pointers.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<System::IsSmartPtr<typename collectionT::key_type>::value && System::IsSmartPtr<typename collectionT::mapped_type>::value, void>::type
        for_each_of_Object_mapped_type(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //case k,m
        for (const typename collectionT::value_type& m : c) {
            visitor.add_member(owner, m.first, "-k"); visitor.add_member(owner, m.second, "-m");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections where keys are pointers and values are not.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<System::IsSmartPtr<typename collectionT::key_type>::value && !System::IsSmartPtr<typename collectionT::mapped_type>::value, void>::type
        for_each_of_Object_mapped_type(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //case k
        for (const typename collectionT::value_type& m : c) {
            visitor.add_member(owner, m.first, "-k");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections where values are pointers and keys are not.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<!System::IsSmartPtr<typename collectionT::key_type>::value && System::IsSmartPtr<typename collectionT::mapped_type>::value, void>::type
        for_each_of_Object_mapped_type(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        //case m
        for (const typename collectionT::value_type& m : c) {
            visitor.add_member(owner, m.second, "-m");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for mapped collections and selects proper implementation based on whether keys and/or values are pointers or not.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<!System::IsSmartPtr<typename collectionT::value_type>::value && is_maped_type<collectionT>::value, void>::type
        for_each_of_Object(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        for_each_of_Object_mapped_type(owner, c, visitor);
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for flat (non-mapped) collections of pointers.
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<System::IsSmartPtr<typename collectionT::value_type>::value, void>::type
        for_each_of_Object(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        for (const typename collectionT::value_type& m : c) {
            visitor.add_member(owner, m, "-");
        }
    }

    /// Applies vistitor to owned collection to enumerate all owned poitners.
    /// This implementation stands for flat arry collections of pointers (At this moment it's ararry in ObjectsHolder<>).
    /// @tparam T Owner object type.
    /// @tparam collectionT Collection type.
    /// @param owner Owner object.
    /// @param c Collection to iterate through.
    /// @param visitor Visitor to apply to owned pointers.
    template<typename T, typename collectionT>
    inline typename std::enable_if<std::is_array<collectionT>::value, void>::type
        for_each_of_Object(T *owner, const collectionT &c, for_each_member_visitor &visitor)
    {
        for (const auto & e : c) {
            visitor.add_member(owner, e, "[]");
        }
    }

    //........................................................................................

    /// Register of alive objects. Should be used as singleton only.
    struct object_registr
    {
    private:
        /// Constructs empty register.
        object_registr() {}
        /// Destroys owned data.
        ~object_registr() {}

        // Compares objects with 'less' semantics using instance numbers for reference.
        struct obj_less { bool operator () (const Object *a, const Object *b) const { return System::Details::DbgTools::DBG_InstanceNo(a) < System::Details::DbgTools::DBG_InstanceNo(b); } };

    public:
        /// Type to map object pointers to identifiers.
        typedef std::map<const Object*, int, obj_less> objtoidx_t;
        /// Type to map object identifiers to pointers.
        typedef std::map<int, const Object*> idxtoobj_t;
        /// Set of objects.
        typedef std::set<const Object*, obj_less> set_obj_t;
        /// Set of indexes.
        typedef std::set<int> set_ids_t;

    public:
        /// Singleton accessor interface.
        /// @return Reference to object register.
        static ASPOSECPP_SHARED_API object_registr& inst();

        /// Registers object in internal data structures.
        /// Called by Object constructors, if related defines are enabled.
        /// @param obj Object to register.
        void add(const Object *obj)
        {
            m_objtoidx.insert(objtoidx_t::value_type(obj, System::Details::DbgTools::DBG_InstanceNo(obj)));
            m_idxtoobj.insert(idxtoobj_t::value_type(System::Details::DbgTools::DBG_InstanceNo(obj), obj));
        }
        /// Removes object from internal data structures.
        /// Called by Object destructor, if related defines are enabled.
        /// @param obj Object to remove.
        void remove(const Object *obj)
        {
            const auto objtoidx = m_objtoidx.find(obj);
            if (objtoidx != m_objtoidx.end())
                m_objtoidx.erase(objtoidx);

            const auto idxtoobj = m_idxtoobj.find(System::Details::DbgTools::DBG_InstanceNo(obj));
            if (idxtoobj != m_idxtoobj.end())
                m_idxtoobj.erase(idxtoobj);
        }

        /// Gets map of all known objects.
        /// @return Const reference to data structure that maps objects onto indexes.
        const objtoidx_t& all_set() const
        {
            return m_objtoidx;
        }

        /// Gets a slice of register containing only objects with specified ids and only with reference counter not less than specified value.
        /// @param ids Set of ids of objects to get information for.
        /// @param n_minimum_references Effectively, excludes from return set all objects with reference counter less than specified value; useful to limit output to greatest leaks first.
        /// @return A set of pointers to objects satisfying both conditions applied.
        set_obj_t sub_set(const set_ids_t &ids, uint32_t n_minimum_references = 0) const
        {
            set_obj_t result;
            for (int id : ids)
            {
                idxtoobj_t::const_iterator it = m_idxtoobj.find(id);
                if (m_idxtoobj.end() != it)
                {
                    const Object *o = it->second;

                    if ((uint32_t)o->SharedCount() >= n_minimum_references) {
                        result.insert(o);
                    }
                }
            }
            return result;
        }

        /// Gets a slice of register containing only objects with reference counter not less than specified value.
        /// @param n_minimum_references Effectively, excludes from return set all objects with reference counter less than specified value; useful to limit output to greatest leaks first.
        /// @return A set of pointers to objects with reference counter not less than @p n_minimum_references.
        set_obj_t sub_set(uint32_t n_minimum_references) const
        {
            set_obj_t result;
            for(const objtoidx_t::value_type &vt : m_objtoidx)
            {
                if ((uint32_t)vt.first->SharedCount() >= n_minimum_references) {
                    result.insert(vt.first);
                }
            }
            return result;
        }

        /// Gets a full set of objects referencing specified subset directly or indirectly.
        /// @param ids Identifiers of objects to back-trace.
        /// @param deep Depth limit; references longer than this won't be tracked.
        set_obj_t back_trace(const set_ids_t &ids, uint32_t deep)
        {
            typedef for_each_member_visitor::map_id_ref_to_ids rmap_t;
            typedef for_each_member_visitor::node_info ni_t;
            typedef for_each_member_visitor::node_info_ex ni_ex_t;

            System::DBG::for_each_member_visitor vizitor;

            for (const System::DBG::object_registr::objtoidx_t::value_type& vt : System::DBG::object_registr::inst().all_set())
            {
                    vt.first->DBG_for_each_member(vizitor);
            };
            vizitor.build_back_references();

            set_obj_t result;
            set_ids_t to_visit = ids, visited, deep_set;

            for (int id : ids)
            {
                idxtoobj_t::const_iterator it = m_idxtoobj.find(id);
                if (m_idxtoobj.end() != it) {
                    result.insert(it->second);
                }
            }

            while (!to_visit.empty())
            {
                int id = *to_visit.begin();
                visited.insert(id);

                rmap_t::const_iterator it = vizitor.relations.find(ni_ex_t(id));
                if (vizitor.relations.end() != it)
                {
                    const ni_ex_t &ni = it->first;
                    for (int _id : ni.back_references)
                    {
                        if (visited.end() == visited.find(_id))
                        {
                            result.insert(m_idxtoobj.find(_id)->second);
                            to_visit.insert(_id);

                            if (deep > 0) {
                                rmap_t::const_iterator it_deep = vizitor.relations.find(ni_ex_t(_id));
                                if (vizitor.relations.end() != it_deep) {
                                    for (const ni_t& _ni : it_deep->second) { deep_set.insert(_ni.id); }
                                }
                            }

                        }
                    }
                }

                --deep;

                to_visit.erase(id);
            }

            for(int id : deep_set) { result.insert(m_idxtoobj.find(id)->second); }

            return result;
        }

        /// Renumbers all objects to make sure the indexes are consequental and start from 1.
        /// Used by 'stable_gv_file' option.
        void renumber_objects()
        {
            m_idxtoobj.clear();

            int index = 1;
            for (auto &pair : m_objtoidx)
            {
                System::Details::DbgTools::DBG_SetInstanceNo(pair.first, index);
                pair.second = index;
                m_idxtoobj[index] = pair.first;
                ++index;
            }
        }

        /// Deletes register contents.
        void clear()
        {
            m_objtoidx.clear();
            m_idxtoobj.clear();
        }

    private:
        /// Maps object pointers to indexes.
        objtoidx_t m_objtoidx;
        /// Maps indexes to objects pointers.
        idxtoobj_t m_idxtoobj;
    };

    //........................................................................................
    /// Collects information on loop references.
    /// @param include_weak Include weak references.
    /// @return Visitor to use information from.
    ASPOSECPP_SHARED_API System::DBG::for_each_member_visitor DBG_initialize_object_graph(bool include_weak);
    
    /// Collects and dumps information on loop references using graphviz format.
    /// @param filename Output filename (most probably, graphviz file).
    /// @param visitor Visitor to use information from.
    /// @param skip_singleton_nodes If true, singleton nodes won't be present in output.
    /// @param cycles_only If true, use an extended algorithm for filtering cyclic dependencies.
    /// @param include weak references
    ASPOSECPP_SHARED_API void DBG_dump_object_graph(const std::string filename, bool skip_singleton_nodes = false, bool include_weak = false, bool cycles_only = false);

    /// Dumps collected information on loop references using graphviz format.
    /// @param o Output stream (most probably, graphviz file).
    /// @param visitor Visitor to use information from.
    /// @param skip_singleton_nodes If true, singleton nodes won't be present in output.
    /// @param include weak references
    ASPOSECPP_SHARED_API void DBG_build_graphviz_script(std::ostream &o, System::DBG::for_each_member_visitor &visitor, bool skip_singleton_nodes = true, bool include_weak = false);

    /// Dumps collected information on loop references using graphviz format.
    /// @param o Output stream (most probably, graphviz file).
    /// @param visitor Visitor to use information from.
    /// @param include_only Dump only object id's from the set
    /// @param skip_singleton_nodes If true, singleton nodes won't be present in output.
    /// @param include weak references
    ASPOSECPP_SHARED_API void DBG_build_graphviz_script(std::ostream &o, System::DBG::for_each_member_visitor &visitor, System::DBG::object_registr::set_ids_t &include_only, bool skip_singleton_nodes = true, bool include_weak = false);
} }

#endif
