# NIIAS screening task
Goal is to filter ground points from the rest of point cloud. 
#### My solution
I went for a simple approach, where we are looking through all of the points, sorted by Z axis, and trying to find "the most dense" group of points, limited by some range. The idea is, that almost half of the radar range is falling onto ground (all of the points below red line):
![radar thingy](https://i.imgur.com/irIR75S.png)

If we're assuming, that ground is mostly flat, it becomes an easy task of looking for dense point cloud group.

#### Result
![radar thingy](https://i.imgur.com/ejfJ6IC.png)
Green shaded points are filtered as "ground"