#!/bin/python

import vtk
import math

view = vtk.vtkContextView()
view.GetRenderer().SetBackground(1.0, 1.0, 1.0)
view.GetRenderWindow().SetSize(400, 300)
 
chart = vtk.vtkChartXY()
view.GetScene().AddItem(chart)
chart.SetShowLegend(True)
 
table = vtk.vtkTable()
 
arrX = vtk.vtkFloatArray()
arrX.SetName("X Axis")
table.AddColumn(arrX)
 
arrC = vtk.vtkFloatArray()
arrC.SetName("Cosine")
table.AddColumn(arrC)
 
arrS = vtk.vtkFloatArray()
arrS.SetName("Sine")
table.AddColumn(arrS)
 
arrT = vtk.vtkFloatArray()
arrT.SetName("Sine - Cosine")
table.AddColumn(arrT)
 
numPoints = 40
inc = 7.5 / (numPoints-1)
table.SetNumberOfRows(numPoints)
for i in range(numPoints):
    table.SetValue(i, 0, i * inc)
    table.SetValue(i, 1, math.cos(i * inc) + 0.0)
    table.SetValue(i, 2, math.sin(i * inc) + 0.0)
    table.SetValue(i, 3, math.sin(i * inc) - math.cos(i * inc))
 
points = chart.AddPlot(vtk.vtkChart.POINTS)
points.SetInputData(table, 0, 1)
points.SetColor(0, 0, 0, 255)
points.SetWidth(1.0)
points.SetMarkerStyle(vtk.vtkPlotPoints.CROSS)
 
points = chart.AddPlot(vtk.vtkChart.POINTS)
points.SetInputData(table, 0, 2)
points.SetColor(0, 0, 0, 255)
points.SetWidth(1.0)
points.SetMarkerStyle(vtk.vtkPlotPoints.PLUS)
 
points = chart.AddPlot(vtk.vtkChart.POINTS)
points.SetInputData(table, 0, 3)
points.SetColor(0, 0, 255, 255)
points.SetWidth(1.0)
points.SetMarkerStyle(vtk.vtkPlotPoints.CIRCLE)
 
view.GetRenderWindow().SetMultiSamples(0)
view.GetInteractor().Initialize()
view.GetInteractor().Start()
