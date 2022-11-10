
# importing all modules
from dash import Dash, dcc, html, Input, Output
import plotly.express as px
import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots


# creating the app
app = Dash(__name__)
colors = {
    'background': '#111111',
    'text': '#7FDBFF'
}
# --------------------------------------------------------------
df=pd.read_excel('dashboard.xlsx')
totac=df.groupby('Date')['Outcome'].count()
totsuc=df[df['Outcome']=='Success'].groupby('Date')['Outcome'].count()
totnsuc=df[df['Outcome']=='Failure'].groupby('Date')['Outcome'].count()
dfsd=totac[totsuc.index]


# --------------------------------------------------------------
# first plot
fig = go.Figure()
fig.add_trace(go.Scatter(x=totac.index, y=totac,
                    mode='lines',
                    name='Total'))
fig.add_trace(go.Scatter(x=totsuc.index, y=totsuc,
                    mode='lines',
                    name='Success'))
fig.add_trace(go.Scatter(x=totnsuc.index, y=totnsuc,
                    mode='lines',
                    name='Failure'))

fig.add_trace(go.Scatter(x=totsuc.index, y=totsuc*100/dfsd,
                    mode='lines',
                    name='Ratio%'))
fig.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': "Question -a",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)

# second plot ---------------------------------------------------------------------------------------
def success(outcome):
    if outcome == "Success":
        return 1
    else:
        return 0
def failure(outcome):
    if outcome == "Failure":
        return 1
    else:
        return 0

df["Success"] = df.Outcome.apply(success)
df["Failure"] = df.Outcome.apply(failure)
sucess_in_state = df.groupby("State")["Success"].sum()
failure_in_state = df.groupby("State")["Failure"].sum()



fig1 = go.Figure()

fig1.add_trace(go.Bar(x=sucess_in_state.index, y=sucess_in_state.values,
                    name='successful calls'))

fig1.add_trace(go.Bar(x=failure_in_state.index, y=failure_in_state.values, 
                    name='failed calls'))
fig1.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': "Question -b",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)



# third question------------------------------------------------------------------------------------
a='Failure','Success'
sizes=[df[df['Outcome']=='Success'].shape[0],df[df['Outcome']=='Failure'].shape[0]]
fig2 = go.Figure(data=[go.Pie(labels = a, values = sizes)])
fig2.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': "Question -c",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)

# 4th question-----------------------------------------------------------------------------------------
totac=df.groupby('State')['Outcome'].count().reset_index()  
totsuc=df[df['Outcome']=='Success'].groupby('State')['Outcome'].count().reset_index()
totnsuc=df[df['Outcome']=='Failure'].groupby('State')['Outcome'].count().reset_index()
dfm = pd.merge(totac, totsuc, on='State').fillna(0)
dfm['ratio']=dfm['Outcome_y']/dfm['Outcome_x']
best=dfm['ratio'].max()
best=dfm.loc[dfm['ratio'].idxmax()]
print('best state is',best)


fig5 = go.Figure()
fig5.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': 'Question - d----------------> The best state is printed' ,
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)


# question 5 ---------------------------------------------------------------------------------------------
totac1=df.groupby('State')['Outcome'].count()
totsuc1=df[df['Outcome']=='Success'].groupby('State')['Outcome'].count()
totnsuc1=df[df['Outcome']=='Failure'].groupby('State')['Outcome'].count()

fig3 = make_subplots(rows=1, cols=2, 
    column_widths=[0.5, 0.5],specs=[[{"type": "pie"}, {"type": "pie"}]],
    subplot_titles=("successfull calls ", "failure calls"))
fig3.add_trace(row=1, col=1,
    trace=go.Pie(labels=totsuc1.index, values=totsuc1.values,)) 
fig3.add_trace(row=1, col=2,
    trace=go.Pie(labels=totnsuc1.index, values=totnsuc1.values,))

fig3.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': "Question -e",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)



# question-6 --------------------------------------------------------------------------------------------

success_time = df[df["Success"] == 1].groupby("Time_Period")["Success"].count().sort_index()

fig4 = go.Figure()
fig4.add_trace(go.Scatter(x=success_time.index, y=success_time.values, mode='lines',
                    name='Number of successful over time period'))
fig4.update_layout(
    font_family="Courier New",
    font_color="blue",
    title_font_family="Times New Roman",
    title ={
        'text': "Question -f",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'
    }
)
# ------------------------------------------------------------------------
# layout of dashboard ---------------------------------------------------------------------------------
app.layout = html.Div(style={'backgroundColor': colors['background']}, children=[
    html.H1(
        children='Dashboard Assignment',
        style={
            'textAlign': 'center',
            'color': colors['text']
        }
    ),

    html.Div(children='Dashboard using plotly', style={
        'textAlign': 'center',
        'color': colors['text']
    }),
    html.Hr(),
    html.Br(),
    html.Hr(),

    dcc.Graph(
        id='dashboard',
        figure=fig
    ),
    html.Hr(),
    dcc.Graph(
        id='dashboard1',
        figure=fig1
    ),
    html.Hr(),
    dcc.Graph(
        id='dashboard12',
        figure=fig2
    )
    ,
    html.Hr(),
    dcc.Graph(
        id='dashboard5',
        figure=fig5
    ),
    html.Hr(),
    dcc.Graph(
        id='dashboard3',
        figure=fig3
    ),
    html.Hr(),
    dcc.Graph(
        id='dashboard4',
        figure=fig4
    )
])

# ----------------------------------------------------------------
if __name__ == '__main__':
    app.run_server(debug=True)
