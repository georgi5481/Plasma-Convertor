# Plasma-Convertor

This little program has a simple fuction - converting the DXF file created by AutoCAD, making the necessary calculations and turning it into a CNC file.

Feel free to use it or modify it. But please note, if you are gonna use the program as it is at the moment - you are gonna have to use arcs and lines in AutoCAD. 
This program(and my machine) are made for two dimensional(2 axis) cordinates.
First you are gonna have to merge/join the lines so the cutting machine/plasma don't stop cutting after reaching every end of line/arc.
Second you are gonna have to use save as DXF file in the AutoCAD software (better save it as a 2000 AutoCAD.dxf version for escaping future errors) .
Third for achiving a sequence on the cutting path before you click save, click on tools -> options -> DXF options -> mark the select objects -> then OK
After you clicked OK now please mark the polyline/line/arc you would like to start till the last one you want to be saved in the DXF file.
After you saved the DXF file in the DXF folder -> open the convertor -> add the name of the file (without the extension) and add the speed for the speed.
If everything went correct -> the program should write that converting the file was successful.
