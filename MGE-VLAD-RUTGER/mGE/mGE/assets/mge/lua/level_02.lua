function Start()

SetOpenVectorSpike("Normal_Trap_03",-5,0,0);
SetOpenVectorSpike("Normal_Trap_02",5,0,0);
SetOpenVectorSpike("Normal_Trap_01",-5,0,0);
SetOpenVectorSpike("Normal_Trap_04",5,0,0);
SetOpenVectorSpike("Normal_Trap_05",5,0,0);

SetOpenVectorSpike("Shooting_Trap_01",-5,0,0);


SetTrapTrigger("Shooting_Trap_01","Trap_Trigger_01");



SetBeginEndGhost("enemy_02",33.1946980391,0.5,-48.4587374154, 33.1946980391,0.5,-14.7365);
SetBeginEndGhost("enemy_01",40.5501190617,0.5,-22.0818122614, 40.5501190617,0.5,-14.7365);

SetKeyNeededDoor("Door_02",1);
end
