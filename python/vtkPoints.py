#!/bin/python

import vtk
import vtk.util.colors

points = vtk.vtkPoints()
points.InsertNextPoint(0, 0, 0)
points.InsertNextPoint(0, 1, 0)
points.InsertNextPoint(1, 0, 0)
points.InsertNextPoint(0, 0, 1)

pointsPolyData = vtk.vtkPolyData()
pointsPolyData.SetPoints(points)

vertexFilter = vtk.vtkVertexGlyphFilter()
vertexFilter.SetInputData(pointsPolyData)
vertexFilter.Update()                          

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(vertexFilter.GetOutput())

actor = vtk.vtkActor()
actor.SetMapper(mapper)
actor.GetProperty().SetColor(vtk.util.colors.banana)

renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

renderer.AddActor(actor)
renderer.SetBackground(0.,0.,0.)

renderWindowInteractor.Initialize()

#renderer.ResetCamera()
#renderer.GetActiveCamera().Zoom(1.5)

renderWindow.Render()
renderWindowInteractor.Start()

