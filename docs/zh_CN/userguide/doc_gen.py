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

def del_dir(path):
    ls = os.listdir(path)
    for i in ls:
        c_path = os.path.join(path, i)
        if os.path.isdir(c_path):
            del_dir(c_path)
        else:
            os.remove(c_path)
    os.rmdir(path)
    return None


if os.path.exists('_build'):
    print '_build already exist deling'
    del_dir('_build')

os.system("call make.bat html")
os.system("call make.bat latex")
InstallDir('_build\latex', 'C:\gitlab_runner\docs_env\latex')
build = "call build.bat " + "index"
print build
os.system(build)
os.system(build)

curr_dir = os.getcwd()
dir_list = curr_dir.split('\\')
curr_dir_name = dir_list[len(dir_list) - 1]

os.rename("_build\\latex\\index.pdf",'_build\\latex\\' + curr_dir_name + '.pdf')
Install(os.path.abspath(os.path.join(os.getcwd(), "..")) + "/docs_release/pdf",'_build/latex/' + curr_dir_name + '.pdf');
InstallDir(os.path.abspath(os.path.join(os.getcwd(), "..")) + "/docs_release/html/" + curr_dir_name ,'_build/html');
# shutil.move();
