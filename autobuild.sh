#!/bin/bash
set -x

# 获取当前目录
ROOT_DIR=$(pwd)

# 如果 build 目录不存在就创建
mkdir -p "$ROOT_DIR/build"

# 清空 build 目录
rm -rf "$ROOT_DIR/build"/*

# 进入 build 目录并执行编译
cd "$ROOT_DIR/build" &&
    cmake .. &&
    make

