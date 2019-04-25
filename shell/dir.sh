#! /bin/bash
echo "文件:"
ls -l | grep "^-"
docnum=$(ls -l | grep "^-" | wc -l)
echo "目录:"
ls -l | grep "^d"
dirnum=$(ls -l | grep "^d" | wc -l)
echo ------------------------------
echo 此层级工作目录下文件有 $docnum 个
echo 目录有 $dirnum 个

# ~/program02  tree
#.
#├── a
#├── aa
#│   └── aa.c
#├── b
#├── bb
#├── c
#├── cc
#└── dir.sh
