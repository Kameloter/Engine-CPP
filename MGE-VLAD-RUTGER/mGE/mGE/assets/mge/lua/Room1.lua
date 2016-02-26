function Start()
 ConnectStatueToPlate("Pressure_Plate_02","Statue_01");
 ConnectStatueToPlate("Pressure_Plate_01","Statue_02");
 AddPressurePlateToDoor("Door_01","Pressure_Plate_01");
 --AddPressurePlateToDoor("Bridge_01","Pressure_Plate_02");
SetOpenVector("Bridge_01",-25,0,0);
end


