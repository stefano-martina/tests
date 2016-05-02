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

axesActor = vtk.vtkAxesActor()
axesWidget = vtk.vtkOrientationMarkerWidget()
axesWidget.SetOutlineColor(0.9300, 0.5700, 0.1300)
axesWidget.SetOrientationMarker(axesActor)
axesWidget.SetInteractor(renderWindowInteractor)
axesWidget.SetViewport(0.0, 0.0, 0.1, 0.1)
axesWidget.SetEnabled(True)
axesWidget.InteractiveOn()

array1 = vtk.vtkFloatArray()
array1.InsertNextValue(0)
array1.InsertNextValue(1)
array1.InsertNextValue(0)
array1.InsertNextValue(2)

array2 = vtk.vtkFloatArray()
array2.InsertNextValue(3)
array2.InsertNextValue(0)
array2.InsertNextValue(2)
array2.InsertNextValue(1)

unstructuredGrid.GetPointData().SetScalars(array1)
unstructuredGrid2 = vtk.vtkUnstructuredGrid()
unstructuredGrid2.CopyStructure(unstructuredGrid)
unstructuredGrid2.GetPointData().SetScalars(array2)
#polyData = vtk.vtkPolyData()
#polyData.GetPointData().SetScalars(array1)

plotActor = vtk.vtkXYPlotActor()
plotActor.SetTitle("Ma Sticazzi?")
#plotActor.AddDataSetInput(polyData)
plotActor.AddDataSetInput(unstructuredGrid)
plotActor.AddDataSetInput(unstructuredGrid2)
plotWidget = vtk.vtkXYPlotWidget()
#plotWidget.SetOutlineColor(0.9300, 0.5700, 0.1300)
plotWidget.SetXYPlotActor(plotActor)
plotWidget.SetInteractor(renderWindowInteractor)
#plotWidget.SetViewport(0.2, 0.2, 0.4, 0.4)
plotWidget.SetEnabled(True)
#plotWidget.InteractiveOn()

#plotWidget = vtk.QVTKWidget() 
#view = vtk.vtkContextView()
#view.SetInteractor(renderWindowInteractor)
#plotWidget.SetRenderWindow(view.GetRenderWindow())

renderer.ResetCamera()
#interactorStyle.SetWorldUpVector((0.0,1.0,0.0))
#interactorStyle.SetWorldUpVector(renderer.GetActiveCamera().GetViewUp())
print(renderer.GetActiveCamera().GetViewUp())
print(renderer.GetActiveCamera().GetViewShear())
print(renderer.GetActiveCamera().GetPosition())
print(renderer.GetActiveCamera().GetFocalPoint())
camPos = renderer.GetActiveCamera().GetPosition()
renderer.GetActiveCamera().SetPosition((camPos[2],camPos[1],camPos[0]))
renderer.GetActiveCamera().SetViewUp((0.0,0.0,1.0))
#renderer.GetActiveCamera().SetViewShear((1.0,0.0,0.0))
#renderer.GetActiveCamera().Zoom(1.5)

renderWindow.Render()
renderWindowInteractor.Start()

