#!/bin/sh
###
# 分析家数据抓取 http://www.000562.com/data/2011/0410/article_2406.htm
###

url='http://www.000562.com/fxjdata'

if [ ! -d tmp ]
then
	mkdir -v tmp
fi
cd tmp

#2014-2011年间五分钟数据
for y in {2004..2011}
do
	for m in {1..12}
	do
		wget $(printf '%s/%d%02dm.rar' $url $y $m)
	done
done

#2012年五分钟数据(缺12月份)
for m in {1..11}
do
	wget $(printf '%s/2011%02dm.rar' $url $m)
done

#2001-2011全年数据
for y in {2001..2011}
do
	wget $(printf '%s/%dn.zip' $url $y)
done

#其它全年数据
for y in http://www.000562.com/data/stkinfo.rar http://www.000562.com/fxjdata/SPLIT.PWR http://www.000562.com/fxjdata/superstk.fin
do
	wget $y
done

