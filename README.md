# Autostereogram
Creating magic eye type images using shaders :)

## Cool Images
<!-- 
  ffmpeg -i elephant.mp4 -vf "scale=256:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" out.gif
  (Source: https://superuser.com/questions/556029/how-do-i-convert-a-video-to-gif-using-ffmpeg-with-reasonable-quality)
-->
Here's a neat visualization of rotating a depth map (and applying a texture to it):

![elephant with depth](https://github.com/user-attachments/assets/2ae17038-aa31-49ac-95c1-03103e8fe59a)
<!-- MP4 Version: https://github.com/user-attachments/assets/1e4f9044-a055-4ea4-956a-3cc4598b2e93 -->
And here is that depth map as an autostereogram (also known as a magic eye), although the depth parameters migh not be optimal:

<img src="https://github.com/user-attachments/assets/d1f0116f-fa74-47bd-8e84-dde69deb4687" alt="elephant autostereogram" width="600" />

This runs in real time btw, so here is a gif of me moving the elephant around (it is pretty easy to see in the program, but probably harder in the gif):

![elephant animated autostereogram](https://github.com/user-attachments/assets/3ebfb9a6-ea7a-419d-9c5a-14db7890a09e)
