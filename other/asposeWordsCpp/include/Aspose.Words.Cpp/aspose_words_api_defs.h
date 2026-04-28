//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/aspose_words_api_defs.h
#pragma once

#if defined(_MSC_VER)

#define ASPOSE_WORDS_SHARED_API __declspec(dllimport)
#define ASPOSE_WORDS_LOCAL_API
#define ASPOSE_WORDS_SHARED_CLASS
#define ASPOSE_WORDS_SHARED_RTTI_INFO_DECL() RTTI_INFO_DECL_EX(ASPOSE_WORDS_SHARED_API)

#elif defined(__GNUC__)

#define ASPOSE_WORDS_SHARED_API
#define ASPOSE_WORDS_LOCAL_API
#define ASPOSE_WORDS_SHARED_CLASS
#define ASPOSE_WORDS_SHARED_RTTI_INFO_DECL() RTTI_INFO_DECL()

#endif