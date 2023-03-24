// Shader veterx
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'void main() {\n' +
  '  gl_PointSize = 10.0;\n' +
  '  gl_Position = a_Position;\n' +
  '}\n';

// fragment shader
  var FSHADER_SOURCE =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' +  // 
  'void main() {\n' +
  '  gl_FragColor = u_FragColor;\n' +
  '}\n';


  // main function to initialize the canva---webgl
function main() {
  var canvas = document.getElementById('webgl');
  var gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }
  var a_Position = gl.getAttribLocation(gl.program, 'a_Position');
  if (a_Position < 0) {
    console.log('Failed to get the storage location of a_Position');
    return;
  }
  initEventHandlers(canvas, gl, a_Position);
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  drawDots(gl, a_Position);
}



// var g_colors = [1.0, 1.0, 0.0, 1.0]

// ---------------------------------------------------------------------------------------------------------------
// function to draw the points
function drawDots(gl, a_Position) {
  var new_array = []
  var xs = []
  var ys = []
  var xys = []
  var step = 0.01;
  t = 0;
  
  Q_points.forEach(point => {
    new_array.push(point[0]); new_array.push(point[1]);
  });
  GL_Points = new_array;
  gl.clear(gl.COLOR_BUFFER_BIT);

  current_points = Q_points[0]
  current_index = 0
  for (i=0;i<=(Q_points.length/4)+1;i++){
    current_index = i*3;
    console.log(current_index)
    while (t <= 1) {

      // formula
      var first = -1 * t ** 3 + 3 * t ** 2 - 3 * t + 1;
      var second = 3 * t ** 3 - 6 * t ** 2 + 3 * t;
      var third = -3 * t ** 3 + 3 * t ** 2;
      var fourth = -1 * t ** 3 + 3 * t ** 2 - 3 * t + 1;
      var fifth = 3 * t ** 3 - 6 * t ** 2 + 3 * t;
      var sixth = -3 * t ** 3 + 3 * t ** 2;

      x = (first) * current_points[0] + (second) * Q_points[current_index + 1][0] + (third) * Q_points[current_index + 2][0] + t ** 3 * Q_points[current_index + 3][0];
      y = (fourth) * current_points[1] + (fifth) * Q_points[current_index + 1][1] + (sixth) * Q_points[current_index + 2][1] + t ** 3 * Q_points[current_index + 3][1];
      xs.push(x)
      ys.push(y)
      xys.push(x)
      xys.push(y)
      t += step
    }
    t = 0
    current_points = Q_points[current_index + 3]
  }
  
  
  q_lines = [];
  for (var i = 0; i < Q_points.length; i += 1) {
    q_lines.push(Q_points[i][0])
    q_lines.push(Q_points[i][1])
  }

  var vertices = new Float32Array(xys);
  var n = xys.length/2; 
  var lines = new Float32Array(q_lines);
  var linesN = q_lines.length / 2;

  var u_FragColor = gl.getUniformLocation(gl.program, 'u_FragColor');
  if (!u_FragColor) {
    console.log('Failed to get the storage location of u_FragColor');
    return;
  }

  // changing the color to red
  gl.uniform4f(u_FragColor, 1, 0, 0, 1)

  var vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }
 

  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, lines, gl.STATIC_DRAW);

  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);
  gl.drawArrays(gl.LINE_STRIP, 0, linesN);


  var vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }


  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);

  // changing color to green
  gl.uniform4f(u_FragColor, 0, 1, 0, 1)
  gl.drawArrays(gl.LINE_STRIP, 0, n);


  var vertexBuffer = gl.createBuffer();
  if (!vertexBuffer) {
    console.log('Failed to create the buffer object');
    return -1;
  }
  
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, lines, gl.STATIC_DRAW);
  gl.vertexAttribPointer(a_Position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_Position);

  // changing the color to red
  gl.uniform4f(u_FragColor, 1, 0, 0, 1)
  gl.drawArrays(gl.POINTS, 0, linesN);

}


// ---------------------------------------------------------------------------------------------------
// coordinates of points
var Q_points = [
  [-0.5, -0.4],
  [-0.85, -0.15],
  [-0.86, 0.42],
  [-0.72, 0.42],
  [-0.59, 0.42],
  [-0.45, 0.15],
  [-0.35, 0.05],
  [-0.20, -0.07],
  [-0.1, -0.2],
  [0, -0.2],
  [0.12, -0.2],
  [0.3, -0.21],
  [0.35, 0.05],
  [0.41, 0.33],
  [0.6, 0.34],
  [0.72, 0.3],
  [0.84, 0.27],
  [0.87, -0.2],
  [0.55, -0.5]
]
// This array will contain the location of mouse
var GL_Points = []; 

// ---------------------------------------------------------------------------------------------------
// function to detect the motion of mouse and get the new locations
function initEventHandlers(canvas, gl, a_Position) {
  var dragging = false;      
  var lastX = -1, lastY = -1;   // Last position of the mouse
  var index = 0;
  canvas.onmousedown = function (ev) {   // Mouse is pressed
    var x = ev.clientX, y = ev.clientY;
    var rect = ev.target.getBoundingClientRect();
    if (rect.left <= x && x < rect.right && rect.top <= y && y < rect.bottom) {
      lastX = x; lastY = y;
      mouseCoordX = (lastX - 200) / 200;
      mouseCoordY = -1*(lastY - 200) / 200;
      for (var i=0; i < Q_points.length; i++) {
        if ((Q_points[i][0] - 0.05 <= mouseCoordX && mouseCoordX <= Q_points[i][0] + 0.05) && (Q_points[i][1] - 0.05 <= mouseCoordY && mouseCoordY <= Q_points[i][1] + 0.05)) {
          index = i;
        }
      };
      dragging = true;
    }
  };

  canvas.onmouseup = function (ev) { dragging = false; }; 

  canvas.onmousemove = function (ev) { // Mouse is moved
    var x = ev.clientX, y = ev.clientY;
    if (dragging) {
      mouseCoordX = (x - 200) / 200;
      mouseCoordY = -1 * (y - 200) / 200;

      prev_coords = Q_points[index]
      new_coords = [mouseCoordX, mouseCoordY]
      changed_coords = [new_coords[0] - prev_coords[0], new_coords[1] - prev_coords[1]]

      Q_points[index] = [mouseCoordX, mouseCoordY];
      Q_points[index] = [mouseCoordX, mouseCoordY];

      
      if ((index) % 3 == 0 && index != 0 && index != Q_points.length-1 ){
        Q_points[index + 1][0] += changed_coords[0]
        Q_points[index + 1][1] += changed_coords[1]

        Q_points[index - 1][0] += changed_coords[0]
        Q_points[index - 1][1] += changed_coords[1]
      }
      
      if ((index + 1) % 3 == 0 && index != 0 && index != Q_points.length-2 && index != Q_points.length-1) {
        Q_points[index + 2][0] += -changed_coords[0]
        Q_points[index + 2][1] += -changed_coords[1]

      }
      if ((index - 1) % 3 == 0 && index != 0 && index != 1 && index != Q_points.length-1) {

        Q_points[index - 2][0] += -changed_coords[0]
        Q_points[index - 2][1] += -changed_coords[1]

      }  
      drawDots(gl, a_Position);
      
    }
    lastX = x, lastY = y;
  };
}

