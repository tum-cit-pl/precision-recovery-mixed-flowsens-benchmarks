#!/usr/bin/python3
import sys
from functools import cmp_to_key

replacements = [
    ('linux-3.14--drivers--spi--spi-tegra20-slink.ko.cil.i', 'tegra20'),
    ('linux-3.14--drivers--media--platform--marvell-ccic--cafe_ccic.ko.cil-1.i', 'marvell1'),
    ('linux-3.14--drivers--media--platform--marvell-ccic--cafe_ccic.ko.cil-2.i', 'marvell2'),
    ('linux-3.14--drivers--usb--misc--adutux.ko.cil.i', 'adutux'),
    ('linux-3.14--drivers--usb--misc--iowarrior.ko.cil.i', 'iowarrior'),
    ('linux-3.14--drivers--net--irda--w83977af_ir.ko.cil.i', 'w83977af'),
    ('ctrace_comb.c', 'ctrace'),
    ('pfscan_comb.c', 'pfscan'),
    ('knot_comb.c', 'knot'),
    ('aget_comb.c', 'aget'),
    ('linux-3.14--drivers--net--irda--nsc-ircc.ko.cil.i', 'nsc'),
    ('smtprc_comb.c', 'smtprc'),
    ('ypbind_comb.c', 'ypbind'),
    ('zmap.c', 'zmap'),
    ('wrk.c', 'wrk'),
    ('vanitygen.c', 'vanitygen'),
    ('uthash.h', 'uthash'),
    ('sysbench-fixed.c', 'sysbench-fixed'),
    ('snoopy.c', 'snoopy'),
    ('shairport.c', 'shairport'),
    ('procDump.c', 'procDump'),
    ('pingfs.c', 'pingfs'),
    ('pianobar.c', 'pianobar'),
    ('nnn.c', 'nnn'),
    ('mirai-fixed.c', 'mirai-fixed'),
    ('libfreenet.c', 'libfreenet'),
    ('libfaketime.c', 'libfaketime'),
    ('libaco.c', 'libaco'),
    ('level-ip.c', 'level-ip'),
    ('klib.c','klib'),
    ('fzy.c', 'fzy'),
    ('easyLogger.c','easyLogger'),
    ('dump1090.c','dump1090'),
    ('dnspod-sr-fixed.c','dnspod-sr-fixed'),
    ('cava.c','cava'),
    ('cThreadPool.c','cThreadPool'),
    ('brubeck.c','brubeck'),
]

file = sys.argv[1]

with open(file, 'r') as f:
    lines = f.readlines()
rewritten_lines=[]

for line in lines:
    rewritten = False
    for (i, (original, replacement)) in enumerate(replacements):
        rewritten_line = line.replace(original, replacement)
        if rewritten_line != line:
            rewritten_lines.append((rewritten_line, i))
            rewritten = True
            break
    if not rewritten:
        rewritten_lines.append((line, -1))
rewritten_lines = sorted(rewritten_lines, key=cmp_to_key(lambda x, y: x[1] - y[1]))

with open(file, 'w') as f:
    f.truncate(0)
    for (rewritten_line, _) in rewritten_lines:
        f.write(rewritten_line)
