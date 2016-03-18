function Start()
ConnectStatueToPlate("Pressure_Plate_01","PushStatue");
AddPressurePlateToDoor("Gate3x3_01","Pressure_Plate_01");

SetKeyNeededDoor("Gate3x3_02",1);
SetKeyNeededDoor("Gate3x3_03",2);
SetKeyNeededDoor("Gate3x3_04",3);
SetKeyNeededDoor("Gate3x3_05",100);
SetKeyNeededDoor("Gate3x3_06",100);

end
