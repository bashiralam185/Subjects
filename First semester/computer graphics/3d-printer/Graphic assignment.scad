//creating cubes for the first assignent

//Question-1

//cube([2.5, 2, 2]);
//translate([2, -2, 0]){
  //  cube([3.5, 6, 2]);
    //translate([3, -2, 0]){
      //  cube([2, 10, 2]);
    //}   
//}




//Question -2
//color("#54F1A6"){
//cube([2, 2, 4]);
//translate([2, 0, 0]){
  //  cube([4, 4, 4]);
    //translate([4, 0, 0]){
      // cube([2, 8, 4]); 
       //translate([2, 0, 0]){
         //  cube([2, 10, 4]);  
        //} 
    //}
    
//}
//}






// Question -3 
//module first_part(){
//difference(){
//color("#45B680", 1){
  //  difference(){
    //    cube([3, 5, 2]);
      //  translate([0.02, 0.02, 0.02]){
        //    cube([2.9, 5, 2]);
    //}  
  //}
//}
//translate([0.2, 0.2, 0.2]){
//cube([2.6, 6, 2]);
//}
//}
//}
//module part_two() {
//color("#45B680"){
  //  difference(){
    //difference(){
    //difference(){
     //   cube([9, 3, 2]);
       // translate([0.05, 0.05, 0.05]){
         //   cube([8.9, 2.9, 2]);
        //}
    //}
    //translate([3, -1, 0.05]){
    //cube([2.9, 2, 2]);
    //}
//}
//translate([1.5, 2.5, 0.05]){
//cube([6, 1, 2]);
//}
//}
//}
//}

//module third_part(){
//color("#45B680"){
  //  difference(){
    //cube([6, 2, 2]);
      //  translate([0.05, -0.05, 0.05]){
        //    cube([5.9, 2, 2]);
        //}
    //}    
//}
//}


//first_part();
//translate([-3, 5, 0]){
//part_two();
//}
//translate([-1.5, 8, 0]){
//third_part();
//}











//Question - 4
//color("#59EFD9", 1){
    //cube([2, 4, 3]);
    //translate([2, -2,0]){
        //cube([4, 8, 3]);
        //translate([4, -4, 0]){
            //cube([2, 16, 3]);
            //translate([2, -2, 0]){
                //cube([4, 20, 3]);
                //translate([4, 2, 0]){
                    //cube([2, 16, 3]);
                //}
            //}
        //}
    //}
//}







//Question - 5
//module upper_part(){
//color("#42CFB6"){
  //  rotate([0, 45, 0]){
    //cube([14.142, 3, 14.142]);
//}
//}
//}

//translate([0, 0, 10]){
//upper_part();
//}
//color("#42CFB6"){
//cube([20, 3, 10]);
//}













// Question -6
module tri2(){
difference(){
difference(){
cube([3, 2, 4]);
translate([2, 0,-0.5]){
rotate([0, 0, 57]){
    translate([0.6, -2, 0]){
cube([5, 6, 5]);
    }
}
}
}
translate([3, -2.4, 0.02]){
rotate([0, 0, 57]){
cube([2, 6, 5]);
}
}
}
}

module tri(){
difference(){
difference(){
cube([3, 2, 4]);
    translate([0, 0, 0.02]){
    rotate([0, 0, -57]){
        cube([5, 5, 5]);
    }
}
}
translate([0, 0.04, -0.5]){
rotate([0, 0, 33]){
        cube([5, 5, 5]);
    }
}
}
}

color("#25A5D4"){
difference(){
cube([13, 5, 4]);
translate([0.05, 0.05, 0.05]){
    cube([12.9, 5, 4]);
}
}

translate([3, 4.999, 0]){
difference(){
cube([7, 2, 4]);
translate([-1, -0.02, 0.02]){
    cube([9, 2, 4]);
}
}
}

translate([0, 5, 0]){
tri();
}
translate([10, 5, 0]){
tri2();
}
}





//Question - 7color("#42CFB6"){
//        translate([-3.5, 3, 0]){
  //          cylinder(r=3.5, h=2, $fn=8);
//}
  //      translate([-5.9, 2, 0]){
    //        cylinder(r=3.5, h=2, $fn=8);
//}
//}






