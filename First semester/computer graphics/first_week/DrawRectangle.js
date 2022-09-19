// DrawRectangle.js
function main() {
    // Retrieve <canvas> element
    var canvas = document.getElementById('example');
    if (!canvas) {
    console.log('Failed to retrieve the <canvas> element');
    return;
    }
    // Get the rendering context for 2DCG
    var ctx = canvas.getContext('2d');
    var ct = canvas.getContext('2d');

    // Draw a blue rectangle
ctx.fillStyle = 'rgba(0, 0, 255, 1.0)'; // Set a blue color
ctx.fillRect(10, 10, 10, 10); // Fill a rectangle with the color
ct.fillStyle = 'rgba(255, 100, 0, 1.0)'; // Set a blue color
ct.fillRect(10, 100, 10, 10); // Fill a rectangle with the col
}