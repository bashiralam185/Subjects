 // 
   // Vertex shader program
   var VSHADER_SOURCE =
    // x' = x cos b - y sin b
    // y' = x sin b + y cos b
    // z' = z
    'attribute vec4 a_Position;\n' +
    'uniform float u_CosB, u_SinB;\n' +
    'void main() {\n' +
   '  gl_Position.x = a_Position.x * u_CosB - a_Position.y * u_SinB;\n'+
   '  gl_Position.y = a_Position.x * u_SinB + a_Position.y * u_CosB;\n'+
   '  gl_Position.z = a_Position.z;\n' +
   '  gl_Position.w = 1.0;\n' +
   '}\n';
//  RotatedTriangle.js
    // Vertex shader program
  var VSHADER_SOURCE =
     // x' = x cos b - y sin b
     // y' = x sin b + y cos b                             Equation 3.3
     // z' = z
     'attribute vec4 a_Position;\n' +
     'uniform float u_CosB, u_SinB;\n' +
     'void main() {\n' +
   '  gl_Position.x = a_Position.x * u_CosB - a_Position.y *u_SinB;\n'+
  '  gl_Position.y = a_Position.x * u_SinB + a_Position.y * u_CosB;\n'+
   '  gl_Position.z = a_Position.z;\n' +
   '  gl_Position.w = 1.0;\n' +
   '}\n';
   // Fragment shader program
    //   ...
   // Rotation angle
   var ANGLE = 30.0;

   function main() {
        // ...
      // Set the positions of vertices
      var n = initVertexBuffers(gl);
        //  ...
      // Pass the data required to rotate the shape to the vertex shader
      var radian = Math.PI * ANGLE / 180.0; // Convert to radians
      var cosB = Math.cos(radian);
      var sinB = Math.sin(radian);

      var u_CosB = gl.getUniformLocation(gl.program, 'u_CosB');
      var u_SinB = gl.getUniformLocation(gl.program, 'u_SinB');
        //  ...
   gl.uniform1f(u_CosB, cosB);
   gl.uniform1f(u_SinB, sinB);

      // Set the color for clearing <canvas>
        //  ...
      // Draw a triangle
      gl.drawArrays(gl.TRIANGLES, 0, n);
   }

   function initVertexBuffers(gl) {
      var vertices = new Float32Array([
        -0.5, -0.5,  0.5, -0.5,  0, 0.5
      ]);
      var n = 3; // The number of vertices
        //  ...
      return n;
   }