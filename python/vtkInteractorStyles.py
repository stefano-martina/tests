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
unstructuredGrid.InsertNextCell(vtk.VTK_TETRA, 4, [0,1,2,3])

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

#interactorStyle = vtk.vtkInteractorStyleFlight()
interactorStyle = vtk.vtkInteractorStyleUnicam()

renderer.AddActor(actor)
renderer.SetBackground(0.3,0.6,0.3)

renderWindowInteractor.Initialize()
renderWindowInteractor.SetInteractorStyle(interactorStyle)


#renderer.ResetCamera()
#renderer.GetActiveCamera().Zoom(1.5)

renderWindow.Render()
renderWindowInteractor.Start()

