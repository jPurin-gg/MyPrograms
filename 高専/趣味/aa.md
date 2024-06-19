# gnuplot で描画してみます

とりあえずチュートリアルに載っている簡単なグラフから

```gnuplot {cmd=true hide=true output="html"}
set terminal svg
set title "Simple Plots" font ",20"
set key left box
set samples 50
set style data points

plot [-10:10] sin(x),atan(x),cos(atan(x))
```
# gnuplotで描画してみます

DEMOからきれいなグラフ

~~~gnuplot {cmd=true }
set terminal svg
unset border
set key title "splot for [scan=1:*] 'whale.dat' index scan" center
set key bmargin center horizontal Right noreverse enhanced autotitle nobox
set key noinvert samplen 0.6 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 6
set style increment default
set view 38, 341, 1, 1
unset xtics
unset ytics
unset ztics
set title "Iteration over all available data in a file" 
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback
set lmargin at screen 0.09
set rmargin at screen 0.9
splot for [i=1:*] "whale.dat" index i title sprintf("scan %d",i) with lines
~~~