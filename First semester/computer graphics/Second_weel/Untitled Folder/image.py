
# import
import arcade
  
# Open the window. Set the window title and 
# dimensions (width and height)
arcade.open_window(600, 600, "Draw  a triangle for GfG ")
  
# set background color
arcade.set_background_color(arcade.color.BLACK)
  
# Start the render process.
arcade.start_render()
  
# draw triangle
arcade.draw_triangle_filled(300, 200,
                            80, 80,
                            100, 300,
                            arcade.color.YELLOW)
  
# finish drawing
arcade.finish_render()
  
# display everything
arcade.run()