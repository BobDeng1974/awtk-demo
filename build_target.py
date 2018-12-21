#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
from os import path   
import sys
import fnmatch
import tempfile
import time
import importlib
import shutil

def Install(dst_dir,src_dir):
    shutil.copy(src_dir,dst_dir);

def InstallDir(dst_dir,src_dir,name_pattern = '*'):
    if not os.path.exists(dst_dir):
        os.makedirs(dst_dir);
    all_files = os.listdir(src_dir);

    for file in all_files:
        src_file_path = src_dir + os.path.sep + file;
        if os.path.isfile(src_file_path) :
            if fnmatch.fnmatch(file,name_pattern):
                dst_file_path = dst_dir + os.path.sep + file;
                Install(dst_file_path,src_file_path);
        else :
            dst_sub_dir_path = dst_dir + os.path.sep + file
            InstallDir(dst_sub_dir_path,src_file_path,name_pattern)
    return None

#获取当前路径
cur_path = os.getcwd()
print cur_path

os.system("call build_target.bat")
InstallDir("demo/demo_sale/bin", "awtk/bin", "*.exe");

cur_path = os.getcwd()
print cur_path
# os.system("call awtk\\awtk\\bin\\runText.exe")
#os.system("call qt_msvc_templet/build.bat qt_msvc_templet")
