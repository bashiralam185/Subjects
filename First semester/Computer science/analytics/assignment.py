
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

# reading dataset
df=pd.read_excel('dashboard.xlsx')
totac=df.groupby('Date')['Outcome'].count()
totsuc=df[df['Outcome']=='Success'].groupby('Date')['Outcome'].count()
dfsd=totac[totsuc.index]
dfsd1=totac[totsuc.index].sort_values(ascending=False)
totnsuc=df[df['Outcome']=='Failure'].groupby('Date')['Outcome'].count()

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



# second plot
totac=df.groupby('State')['Outcome'].count().reset_index()  
totsuc=df[df['Outcome']=='Success'].groupby('State')['Outcome'].count().reset_index()
totnsuc=df[df['Outcome']=='Failure'].groupby('State')['Outcome'].count().reset_index()


fig1 = make_subplots(rows=1, cols=3)

fig1.add_trace(
    go.Bar(x=totac.index, y=totac.Outcome, name='Total'),
    row=1, col=1
)

fig1.add_trace(
    go.Bar(x=totsuc.index, y=totsuc.Outcome, name='Success'),
    row=1, col=2
)
fig1.add_trace(
    go.Bar(x=totnsuc.index, y=totnsuc.Outcome, name='Failure'),
    row=1, col=3
)
fig1.update_layout(height=600, width=800, title_text="Side By Side Subplots")



# # Third plot
# a='Failure','Success'
# sizes=[df[df['Outcome']=='Success'].shape[0],df[df['Outcome']=='Failure'].shape[0]]
# fig2 = px.pie(names=sizes, title='succes vs failure')
f_s_timeout = df.groupby("Outcome")["Outcome"].count()
fig2 = go.Figure(data=[go.Pie(labels = f_s_timeout.index, values = f_s_timeout.values)])
fig2["layout"]["title"] = "Failure/Success/Timeout"
fig2["layout"]["legend_title"] = "Call outcome"


fig3 = go.Figure()
fig3.add_trace(go.Bar(x=dfsd1.index, y=dfsd1.values,
                    name='Number of successful calls'))
fig3["layout"]["title"] = "Most successfull state by success call"
fig3["layout"]["xaxis"]["title"] = "Date"
fig3["layout"]["yaxis"]["title"] = "Ratio of success"
fig3["layout"]["legend_title"] = "Options"




fig4 = make_subplots(rows=1, cols=2, 
    column_widths=[0.5, 0.5],specs=[[{"type": "pie"}, {"type": "pie"}]],
    subplot_titles=("Calls per state", "successfull calls per state"))
fig4.add_trace(row=1, col=1,
    trace=go.Pie(labels=totac.index, values=totac.values,)) 
fig4.add_trace(row=1, col=2,
    trace=go.Pie(labels=totsuc.index, values=totsuc.values,))


# success_time_out = df[df["Success"] == 1].groupby("Time_Period")["Success"].count().sort_index()

# fig5 = go.Figure()

# fig5.add_trace(go.Bar(x=success_time_out.index, y=success_time_out.values,
#                     name='Number of successful calls'))


# layout of dashboard
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
#  dcc.Dropdown(
#         id="dropdown",
#         options=["Question-1", "Question-2", "Question-3"],
#         value="Question-1",
#         clearable=False,
#     ),
    dcc.Graph(
        id='dashboard',
        figure=fig
    ),
    dcc.Graph(
        id='dashboard1',
        figure=fig1
    ),
    dcc.Graph(
        id='dashboard2',
        figure=fig2
    ),
    dcc.Graph(
        id='dashboard3',
        figure=fig3
    ),
    dcc.Graph(
        id='dashboard4',
        figure=fig4
    )
])

if __name__ == '__main__':
    app.run_server(debug=True)
