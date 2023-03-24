from sqlalchemy import MetaData
from sqlalchemy_schemadisplay import create_schema_graph

graph = create_schema_graph(metadata=MetaData('sqlite:///hr'),
                            show_datatypes=False,  
                            show_indexes=False,
                          
                            rankdir='LR',
                            concentrate=False  
                            )
graph.write_png('FirstQuestion.png')  