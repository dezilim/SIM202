# The graphic title
set terminal gif animate delay 10
# delay is 100 for 1 second between every frame
unset parametric
set size 1, 1
set output 'simulation.gif'
#stats 'earthdata.txt' nooutput
#stats 'sundata.txt' nooutput
#stats 'mercurydata.txt' nooutput
stats 'part1.txt' nooutput
stats 'part2.txt' nooutput
stats 'part3.txt' nooutput
stats 'part4.txt' nooutput
stats 'part5.txt' nooutput
set xrange [-10:10]
set yrange [-10:10]
set zrange [-10:10]
set title 'Gravity Simulation'
set view 0, 90, 1, 1.25
set key 
set tics
#splot 'earthdata.txt' u 1:2:3 with points, 'sundata.txt' u 1:2:3  with points
#do for [ii=1:10] {
#    splot 'earthdata.txt' u 1:2:3 every ::1::ii w l ls 1, \
#          'earthdata.txt' u 1:2:3 every ::ii::ii w p ls 1    
#    splot 'sundata.txt' u 1:2:3 every ::1::ii w l ls 1, \
#          'sundata.txt' u 1:2:3 every ::ii::ii w p ls 1
#}
blue = "rgb '#0000ff'"
red = "rgb '#00cd0'"
orange = "rgb '#F39C12'"
black = "rgb '#000000'"
green =  "rgb '#138d75'" 

set xlabel 'x'
set ylabel 'y'
set zlabel 'z'
set xyplane at -1 


#do for [ii=1:500] {
#    splot 'earthdata.txt' every ::1::ii w l ls 1 title "earth", 'sundata.txt' every ::1::ii w l ls 1 lc @red title "sun", 'mercurydata.txt' every ::1::ii w l ls 1 lc @black title "mercury",\
#          'earthdata.txt' u 1:2:3 every ::ii::ii w p ls 1 notitle, 'sundata.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @red notitle,  'mercurydata.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @black notitle
#}

do for [ii=1:1000] {
    splot 'part1.txt' every ::1::ii w l ls 1 title "planet1", 'part2.txt' every ::1::ii w l ls 1 lc @red title "planet2", 'part3.txt' every ::1::ii w l ls 1 lc @black title "planet3",'part4.txt' every ::1::ii w l ls 1 lc @green title "planet4",'part5.txt' every ::1::ii w l ls 1 lc @orange title "planet5",\
          'part1.txt' u 1:2:3 every ::ii::ii w p ls 1 notitle, 'part2.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @red notitle,  'part3.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @black notitle,'part4.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @green notitle, 'part5.txt' u 1:2:3 every ::ii::ii w p ls 1 lc @orange notitle
}

