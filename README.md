timelogview
===========

Timestamp-savvy GUI universal log viewer in Qt

Inspired by [gst-debug-view][1].

Reads log where each line begins with timestamp (as in `ts '%.s'`) and shows GUI window with 
list of lines and log entry density plot (you can click on it to jump to messages).

To do
======

1. Grepping. Plotting grepped occurence together with total;
2. Code cleanup, MVC;
3. Hiding of uninteresting long entry-less time spans;
4. Zoom-avare density calculation;
5. "Realtime" plotting, as in `feedgnuplot --stream`;
6. Viewing of big log files (not loading entire log into memory);


[1]:http://cgit.freedesktop.org/~cymacs/gst-debug-viewer/
