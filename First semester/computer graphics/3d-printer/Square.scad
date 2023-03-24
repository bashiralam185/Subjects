//
//Filename = Graphic_finalassignment
//Exercise number == 163
//Date of implementation (15/ 15 / 2022)
//Name:  Bashir Alam
//email: bashir.alam_2023@ucentralasia.org
//cohort: computer science



// importing build-in module
use <MCAD/boxes.scad>

// This module creates the round square shape
module Sqr(){
$fa=1;
$fs=0.4;
difference(){
    difference(){
        rotate([0,0,90]){
            roundedBox(size=[100,100,30],radius=3);
        }
        translate([-55, -55, 5]){
            cube([110, 110, 20]);
        }
    }
    translate([-55, -55, -25]){
            cube([110, 110, 20]);
        }
}
}
// creating module that will create the 4 holes in the square
module holes(){
difference(){
    difference(){
        difference(){
            difference(){
                difference(){
                    Sqr();
                    translate([40, 40, -12]){
                        cylinder(h=30, d=10);
                    }
                }
                translate([40, -40, -12]){
                    cylinder(h=30, d=10);
                }
            }
                translate([-40, -40, -12]){
                    cylinder(h=30, d=10);
                }
            }
        translate([-40, 40, -12]){
            cylinder(h=30, d=10);
        }
    }

    translate([0, 0, -6]){
    cylinder(h=20, d=51);
    }
}
}

translate([0, 0, 5]){
holes();
}