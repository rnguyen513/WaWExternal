#  Simple GDI ESP for COD:WAW

Release .exe is /Release/ACRead.exe

Originally used GLFW (OpenGL) but was having tons of issues drawing everything to the screen properly. Switched to GDI instead...

## Pros
+consistent and accurate ESP with health and lines to target
+console monitor to track all living zombies and their position (disabled in release)

## Cons
-something wrong with OpenGL overlay, had to switch to GDI cuz simpler
-GDI graphics are flickery, especially when lots of entities

![example](https://github.com/rnguyen513/WaWExternal/assets/77138030/09c4bbbf-9f8d-485c-ac02-4cbb8fd505f3)
![example2](https://github.com/rnguyen513/WaWExternal/assets/77138030/3d01b70c-71a7-435f-860d-223aeb0a18a8)
