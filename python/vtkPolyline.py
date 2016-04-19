#!/bin/python

import vtk
import vtk.util.colors

points = vtk.vtkPoints()
points.InsertNextPoint(0, 0, 0)
points.InsertNextPoint(0, 1, 0)
points.InsertNextPoint(1, 0, 0)
points.InsertNextPoint(0, 0, 1)

polyLine = vtk.vtkPolyLine()
polyLine.GetPointIds().SetNumberOfIds(4)
polyLine.GetPointIds().SetId(0, 0)
polyLine.GetPointIds().SetId(1, 1)
polyLine.GetPointIds().SetId(2, 2)
polyLine.GetPointIds().SetId(3, 3)
unstructuredGrid = vtk.vtkUnstructuredGrid()
unstructuredGrid.Allocate(1, 1)
unstructuredGrid.InsertNextCell(polyLine.GetCellType(), polyLine.GetPointIds())
unstructuredGrid.SetPoints(points)

mapper = vtk.vtkDataSetMapper()
mapper.SetInputData(unstructuredGrid)

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

