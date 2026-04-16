# Use Debian 13 (Trixie) as the base image
FROM debian:13

# Set environment variables to avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Configure domestic (Tsinghua University) HTTPS software sources
RUN cat > /etc/apt/sources.list.d/debian.sources << 'EOF'
Types: deb
URIs: http://mirrors.tuna.tsinghua.edu.cn/debian
Suites: trixie trixie-updates trixie-backports
Components: main contrib non-free non-free-firmware
Signed-By: /usr/share/keyrings/debian-archive-keyring.gpg

Types: deb
URIs: http://mirrors.tuna.tsinghua.edu.cn/debian-security
Suites: trixie-security
Components: main contrib non-free non-free-firmware
Signed-By: /usr/share/keyrings/debian-archive-keyring.gpg
EOF

# Pre-install HTTPS support, then switch to HTTPS and install the rest
RUN apt-get update \
    && apt-get install -y --no-install-recommends apt-transport-https ca-certificates \
    && sed -i 's|http://|https://|g' /etc/apt/sources.list.d/debian.sources \
    && apt-get update \
    && apt-get install -y \
        python3 \
        python3-pip \
        python3-venv \
        build-essential \
        clang \
        clangd \
        clang-format \
        clang-tidy \
        git \
        curl \
        wget \
        valgrind \
        unzip \
        zip \
        ccache \
        cmake \
        ninja-build \
        gdb \
        tzdata \
        locales \
        sudo \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set timezone and configure locale
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime \
    && echo "Asia/Shanghai" > /etc/timezone \
    && sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen \
    && locale-gen en_US.UTF-8

ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    TZ=Asia/Shanghai

# Create dev user and grant passwordless sudo privileges
RUN groupadd -g 1000 dev \
    && useradd -m -u 1000 -g 1000 -s /bin/bash dev \
    && echo "dev ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/dev \
    && chmod 0440 /etc/sudoers.d/dev

# Switch to the dev user for subsequent installations
USER dev
WORKDIR /home/dev

# Install Miniconda3, initialize conda, and clean up installer
RUN curl -fsSL https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh -o ~/miniconda.sh \
    && bash ~/miniconda.sh -b -f -p /home/dev/miniconda3 \
    && rm ~/miniconda.sh \
    && /home/dev/miniconda3/bin/conda init bash

ENV PATH=/home/dev/miniconda3/bin:$PATH

# Install uv (fast Python package installer) as the dev user
RUN curl -LsSf https://astral.sh/uv/install.sh | sh

# Add uv to PATH
ENV PATH=/home/dev/.local/bin:$PATH

# Install fnm (Fast Node Manager) and Node.js 24
RUN curl -fsSL https://fnm.vercel.app/install | bash \
    && export FNM_PATH="/home/dev/.local/share/fnm" \
    && export PATH="$FNM_PATH:$PATH" \
    && fnm install 24 \
    && fnm default 24

# Make fnm-managed Node.js and fnm itself available in non-interactive shells
ENV PATH=/home/dev/.local/share/fnm/aliases/default/bin:/home/dev/.local/share/fnm:/home/dev/.local/bin:$PATH

# Install Claude Code (AI development tool) globally using npm from fnm-installed Node.js
# Use Taobao npm mirror for faster installation in China
RUN npm config set registry https://registry.npmmirror.com \
    && npm install -g @anthropic-ai/claude-code

# Switch back to root to clean up any temporary files
USER root
RUN apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp/*

# Set the default user back to dev for interactive sessions
USER dev

# Set the default command to bash for interactive use
CMD ["/bin/bash"]