#!/usr/bin/env bash

apuePath=/ddd/ccpp/apue/apue.3e
apueIncludePath=${apuePath}/include
apueLibPath=${apuePath}/lib
apueSignalsPath=${apuePath}/signals

cd ${apueLibPath}; make .

filename=child.c

fullfile=${apueSignalsPath}/${filename};gcc -I${apueIncludePath} -o ${filename%.*} -g ${fullfile} -L${apueLibPath} -lapue
