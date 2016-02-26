function Start()
 ConnectStatueToPlate("Pressure_Plate_02","Statue_01");
 ConnectStatueToPlate("Pressure_Plate_01","Statue_02");
 AddPressurePlateToDoor("Door_01","Pressure_Plate_01");
 AddPressurePlateToDoor("Bridge_01","Pressure_Plate_02");
SetOpenVector("Bridge_01",-28,0,0);
SetOpenVectorBlock("Bridge_03",0,0,6);
SetOpenVectorBlock("Bridge_02",7,0,0);
SetOpenVectorSpike("Shooting_Trap_01",-3,0,0);
SetOpenVectorSpike("Shooting_Trap_02",3,0,0);
SetOpenVectorSpike("Shooting_Trap_03",3,0,0);
end


