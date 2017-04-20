#!/usr/bin/env bash
python ./../test/cpplint.py --extensions=h,hpp,c,cpp --filter=`cat ../test/filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'`
