//
//Filename = Graphic_finalassignment
//Exercise number == 163
//Date of implementation (15/ 15 / 2022)
//Name:  Bashir Alam
//email: bashir.alam_2023@ucentralasia.org
//cohort: computer science




// this module creates the inner parts ( cylinders)
module Cyl(){
    // creating octagonal structure
translate([0,0, 70]){
    difference(){
    cylinder(h=10, d=68,$fn=8);
    translate([0, 0, -1]){
        cylinder(h=12, d= 30);
    }
}
} 
difference(){
    difference(){
        cylinder(80, d=50);
        translate([0, 0, -0.5]){
            cylinder(81, d= 30);
        }
    }

    // taking the inner(side) cyliner out
    rotate([0, 90, 0]){
        translate([-35, 0, -30]){
            cylinder(60, d = 18);
        }
    }
}
}



//calling the modules and fixing the positions using translate
rotate([0 , 180, 0]){
    translate([0, 0, -80]){
        Cyl();
    }
}