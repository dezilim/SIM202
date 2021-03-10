# The graphic title
set terminal gif animate delay 20
# delay is 100 for 1 second between every frame
unset parametric
set size 1, 1
set output 'simulation.gif'
stats 'earthdata.txt' nooutput
stats 'sundata.txt' nooutput
set xrange [-1:1]
set yrange [-1:1]
set zrange [-1:1]
set title 'Gravity Simulation'
set view 60, 30, 1, 1.25
set key off
#splot 'earthdata.txt' u 1:2:3 with points, 'sundata.txt' u 1:2:3  with points
#do for [ii=1:10] {
#    splot 'earthdata.txt' u 1:2:3 every ::1::ii w l ls 1, \
#          'earthdata.txt' u 1:2:3 every ::ii::ii w p ls 1    
#    splot 'sundata.txt' u 1:2:3 every ::1::ii w l ls 1, \
#          'sundata.txt' u 1:2:3 every ::ii::ii w p ls 1
#}
blue = "rgb '#0000ff'"
red = "rgb '#00cd0'"
black = "rgb '#000000'"


set xyplane at -1 


do for [ii=1:100] {
    splot 'earthdata.txt' every ::1::ii w l ls 1 , 'sundata.txt' every ::1::ii w l ls 1 lc @red, 'mercurydata.txt' every ::1::ii w l ls 1 lc @black,\
          'earthdata.txt' u 1:2:3 every ::ii::ii w p ls 1, 'sundata.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @red,  'mercurydata.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @black
}

