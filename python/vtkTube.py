#!/bin/python

import vtk
import vtk.util.colors

points = vtk.vtkPoints()
points.InsertNextPoint(0, 0, 0)
points.InsertNextPoint(0, 1, 0)
points.InsertNextPoint(1, 0, 0)
points.InsertNextPoint(0, 0, 1)

cellArray = vtk.vtkCellArray()
cellArray.InsertNextCell(4)
for i in range(4):
    cellArray.InsertCellPoint(i)
    
polyData = vtk.vtkPolyData()
polyData.SetPoints(points)
polyData.SetLines(cellArray)

profileTubes = vtk.vtkTubeFilter()
profileTubes.SetNumberOfSides(8)
profileTubes.SetInputData(polyData)
profileTubes.SetRadius(.005)

mapper = vtk.vtkPolyDataMapper()
mapper.SetInputConnection(profileTubes.GetOutputPort())

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

axes = vtk.vtkAxesActor()
widget = vtk.vtkOrientationMarkerWidget()
widget.SetOutlineColor(0.9300, 0.5700, 0.1300)
widget.SetOrientationMarker(axes)
widget.SetInteractor(renderWindowInteractor)
widget.SetViewport(0.0, 0.0, 0.1, 0.1)
widget.SetEnabled(True)
widget.InteractiveOn()

renderer.ResetCamera()
camPos = renderer.GetActiveCamera().GetPosition()
renderer.GetActiveCamera().SetPosition((camPos[2],camPos[1],camPos[0]))
renderer.GetActiveCamera().SetViewUp((0.0,0.0,1.0))

renderWindow.Render()
renderWindowInteractor.Start()

