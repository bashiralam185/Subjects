from dash import Dash, html, dcc, Input, Output
import plotly.graph_objects as go
import plotly.express as px
from datetime import date
import pandas as pd
import requests
from bs4 import BeautifulSoup



import sqlite3
con = sqlite3.connect('hr')
df = pd.read_sql_query('select * from employees;', con)
external_stylesheets = ["assets/style.css"]

# -----------------------------------------------Question 1-------------------------------
# connecting tables
data_connected = pd.read_sql("SELECT employees.first_name, jobs.job_title " +
                                "FROM employees " + 
                                "INNER JOIN jobs ON employees.job_id " + 
                                "= jobs.job_id",con)





#----------------------------------------------Question 2 -----------------------------------
con = sqlite3.connect('hr')
jobs=pd.read_sql_query("select * from jobs;",con)
jobs = jobs.iloc[1: , :]
jobs["difference"]=jobs['max_salary']-jobs['min_salary']
job=jobs[['job_title','difference']]
max_salary=job['difference'].max()


app = Dash(__name__)
server =  app.server





colors = {
    'background': '#EEEDE7',
    'text': '#00008B'
}



#-----------------------------------------Layout of the dashboard-------------------------------

app.layout = html.Div(children=[
    html.Div(html.H1(children='Dashboard'), className="heading"),
    html.Div([ html.P('Question one is done in separate file and the screenshot of the output is attached with the file. Please have a look')], className="first_question"),
    html.Div([
        html.P("Question - 2"),
     dcc.Graph(
        id='output',
    )], className='first_plot'),

    html.Div([
        html.P("Question - 3"),
    dcc.RangeSlider(0, max_salary, 1000, value=[0, max_salary],
    id="input3"),
    dcc.Graph(id="output3")], className='second_plot'),

    html.Div([
        html.P("Question - 4"),
    dcc.Graph(
        id='output4',
    )], className="third_plot")
], className="main_layout")


#---------------------------------------Scarpping -------------------------------------
URL = "https://www.itjobswatch.co.uk/jobs/uk/sqlite.do"
r = requests.get(URL)
soup = BeautifulSoup(r.content, 'html5lib') 
table = soup.find('table', attrs = {'class':'summary'}) 
table.find('form').decompose()
table_data = table.tbody.find_all("tr")
table = []
for i in table_data:
    row = []
    rrr = i.find_all("td")
    if len(rrr) == 0:
        rrr = i.find_all("th")
    for j in rrr:
        row.append(j.text)
    table.append(row)

hd = table[1]
hd[0] = "index"

data = pd.DataFrame(table)
data.drop(index=[0,1,2,3,4,5,6,7,10,11,14,15],axis=0,inplace=True)
data.columns = hd
data.set_index("index",inplace=True)
data.reset_index(inplace=True)


# -----------------------------------------------filtering ---------
data['Same period 2021'] = data['Same period 2021'].str.replace('£','')
data['Same period 2021'] = data['Same period 2021'].str.replace(',','')
data['Same period 2021'] = data['Same period 2021'].str.replace('-','0').astype(float)
data['6 months to20 Dec 2022'] = data['6 months to20 Dec 2022'].str.replace('£','')
data['6 months to20 Dec 2022'] = data['6 months to20 Dec 2022'].str.replace(',','').astype(float)
data['Same period 2020'] = data['Same period 2020'].str.replace('£','')
data['Same period 2020'] = data['Same period 2020'].str.replace(',','').astype(float)
data.drop('index', axis=1, inplace=True)



employees = pd.read_sql_query("select * from employees;", con)
jobs = pd.read_sql_query("select * from jobs;", con)

# ---------------------------------------all figrue------------------------------------
@app.callback(
Output('output', 'figure'),
Output('output3', 'figure'),
Output('output4', 'figure'),
Input('input3', 'value')
)
def update_output(value):

    fig = go.Figure()
    fig = px.bar(data_connected, x='job_title',color="job_title")

    minimum=value[0]
    maximum=value[-1]
    fig3 = go.Figure()
    fig3["layout"]["xaxis"]["title"] = "Job"
    fig3["layout"]["yaxis"]["title"] = "Difference between max and min"
    t = job[job["difference"]>=minimum][job["difference"]<=maximum]
    fig3.add_trace(go.Bar(x=t['job_title'], y=t['difference'],
    name='Job differences'))

    


    job_titles = jobs['job_title']
    job_counts = [len(employees[employees['job_id'] == i]) for i in jobs['job_id']]

    percentiles = data
    avg_salary = employees['salary'].mean()
    year = ['10 percentile', '20 percentile', '50 percentile', '90 percentile']


    fig4 = go.Figure()
    fig4.add_trace(go.Scatter(x=year, y=[
                    avg_salary for i in year], name='Average Salary', line=dict(color="#000000")))
    for i in percentiles:
            fig4.add_trace(go.Scatter(
                x=year, y=percentiles[i], name=f'{i}th Percentile', line=dict(color="#30f216")))

    return fig, fig3, fig4

if __name__ == "__main__":
    app.run_server(debug=True)

# if __name__ == '_main_':
#     app.run_server("0.0.0.0", debug=False, port=int(os.environ.get('PORT', 8000)))


