#!/bin/python

import vtk
import vtk.util.colors

points = vtk.vtkPoints()
points.InsertNextPoint(0, 0, 0)
points.InsertNextPoint(0, 1, 0)
points.InsertNextPoint(1, 0, 0)
points.InsertNextPoint(0, 0, 1)

unstructuredGrid = vtk.vtkUnstructuredGrid()
unstructuredGrid.SetPoints(points)
unstructuredGrid.InsertNextCell(vtk.VTK_LINE, 2, [0,1])
unstructuredGrid.InsertNextCell(vtk.VTK_LINE, 2, [1,2])
unstructuredGrid.InsertNextCell(vtk.VTK_LINE, 2, [2,3])

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
renderer.SetBackground(0.3,0.6,0.3)

renderWindowInteractor.Initialize()

#renderer.ResetCamera()
#renderer.GetActiveCamera().Zoom(1.5)

renderWindow.Render()
renderWindowInteractor.Start()

