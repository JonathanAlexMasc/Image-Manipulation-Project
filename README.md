# Image-Manipulation-Project

Welcome! This project was built in C++ and is able to maniulate images in all sorts of ways. Below is a list of all the different operations that the program can perform on an image. 

* Rotate Clockwise
* Rotate CounterClockwise
* Flip on the X-axis 
* Flip on the Y-axis
* Convert to Grayscale
* Convert to Sepia

More than one operation from the above can be performed on an image. Image files are either .ppm or .pgm type. The image data in both of these file types can be ascii or binary. Here's what some of these operations look like on a sample image. 

**Flipping on the X-axis**

![low](https://user-images.githubusercontent.com/94260151/189504431-71f4309f-9160-43bd-87d5-5b64b8b2da46.jpg)           ![houseFlipX](https://user-images.githubusercontent.com/94260151/189504504-e116224a-207c-4860-8435-6fb885a27441.jpg)

**Flipping on the Y-axis**

![low](https://user-images.githubusercontent.com/94260151/189545665-99d2c2da-0830-41c6-9fba-e476a5849764.jpg)       ![houseFlipY](https://user-images.githubusercontent.com/94260151/189545669-62db99a0-5d2a-4fd9-a524-9ffbce6034e7.jpg)

**Rotate Clockwise** 

![low](https://user-images.githubusercontent.com/94260151/189545968-cbd37deb-d0c1-4994-80a6-26d9fc3ada32.jpg)
![houserotC](https://user-images.githubusercontent.com/94260151/189545970-c061d9a5-3bf3-40f1-88ed-5b6298b423cc.jpg)


**Rotate CounterClockwise**

![low](https://user-images.githubusercontent.com/94260151/189545978-cebd01f9-1ef0-4391-9a8a-3876f692ba6e.jpg)
![houserotCC](https://user-images.githubusercontent.com/94260151/189545984-b7948c27-6914-4c2d-b7bd-2e8f89ba231c.jpg)


**Convert to Grayscale**

![low](https://user-images.githubusercontent.com/94260151/189545990-15642cfe-3d2f-4d62-b930-9d601a984249.jpg)
![gray](https://user-images.githubusercontent.com/94260151/189546000-3aa0cacc-0458-4c31-8033-d842d874ed2f.jpg)


**Convert to Sepia** 

![low](https://user-images.githubusercontent.com/94260151/189546006-d2d7052d-408f-427b-b7cd-6ba76144c193.jpg)
![sepia](https://user-images.githubusercontent.com/94260151/189546013-eb0522d1-fbc9-4691-b4d3-f0d7c941f3da.jpg)


**Notes:**
- Grayscale images are outputted in the .pgm only, irrespective of whether the original image was of the type .ppm or .pgm
- The program can also be used to convert ascii image files to binary (P3 -> P6) and vice versa. 
- Dynamic memory allocation is used frequently throughout the program.  


