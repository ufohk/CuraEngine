
# writeGCode()
```plantuml
@startuml
|Progress|
|Raft|
|LayerPlan|
|Communication|
|LayerPlanBuffer|
|#lightgray|GCodeExport|
|#pink|FffGcodeWriter|

|#pink|FffGcodeWriter|
start
#palegreen:getStartExtruder();
|#lightgray|GCodeExport|
:preSetup();
:setSliceUUID();
|#pink|FffGcodeWriter|
if (first mesh_group) then (true)
  |#lightgray|GCodeExport|
  :resetTotalPrintTimeAndFilament();
  :setInitialAndBuildVolumeTemps();
endif

|Communication|
:beginGCode();

|#pink|FffGcodeWriter|
#palegreen:setConfigFanSpeedLayerTime();
#palegreen:setConfigRetractionAndWipe();

if (first mesh_group) then (true)
    #palegreen:processStartingCode();
else
    #palegreen:processNextMeshGroupCode();
endif

repeat
    if (mesh is printed) then (true)
      if (mesh.layers.size() > total_layers) then (true)
        :total_layers = mesh.layers.size();
      endif
    endif
    
    #palegreen:setInfillAndSkinAngles();
repeat while (more mesh) is (true)

#palegreen:setSupportAngles();

|#lightgray|GCodeExport|
:writeLayerCountComment(total_layers);

|#pink|FffGcodeWriter|
repeat
    #palegreen:calculateMeshOrder();
    :store calculateMeshOrder;
repeat while (more mesh) is (true)

#palegreen:calculateExtruderOrderPerLayer();

#palegreen:calculatePrimeLayerPerExtruder();

if (magic_spiralize) then (true)
  #palegreen:findLayerSeamsForSpiralize();
endif

if (has_raft) then (true)
  #palegreen:processRaft();
  
  repeat
    if (extruder_is_used_in_filler_layers) then (true)
        |Raft|
        :getFillerLayerCount();
        |FffGcodeWriter|
        :set process_layer_starting_layer - get_filler_layer_count;
        break
    endif
    
    repeat while (more extruder_is_used_in_filler_layers) is (true)
endif

#palegreen:run_multiple_producers_ordered_consumer();        


:flush layer_plan buffer;

|Progress|
:messageProgressStage(finish);
|#pink|FffGcodeWriter|

|#lightgray|GCodeExport|
:writeRetraction();
|#pink|FffGcodeWriter|
stop
@enduml
```

# getStartExtruder()
```plantuml
@startuml
|#pink|FffGcodeWriter|
start
switch (adhesion_type)
case (SKIRT)
    :skirt_brim_extruder;
case (BRIM)
    :skirt_brim_extruder;
case (RAFT)
    :raft_base_extruder_nr;
case (NONE)
    if (support_enable && support_brim_enable) then (true)
    :support_infill_extruder_nr;
    else
    |SliceDataStorage|
    :getExtrudersUsed();
    |#pink|FffGcodeWriter|
    repeat
        if (extruder_is_used)
            :extruder_nr;
            break
        endif
    repeat while (more extruders) is (true)
    endif
endswitch
stop
@enduml
```

# setConfigFanSpeedLayerTime()
```plantuml
@startuml
|#pink|FffGcodeWriter|
start
    repeat
        :set fan_speed_layer_time_settings;
    repeat while (more extruder train) is (true)
stop
@enduml
```

# setConfigRetractionAndWipe()
```plantuml
@startuml
start
    repeat
        #palegreen:retractionAndWipeConfigFromSettings(extruder);
    repeat while (more extruders) is (true)
    repeat
        #palegreen:retractionAndWipeConfigFromSettings(meshes);
    repeat while (more meshes) is (true)
stop
@endpuml
```

# retractionAndWipeConfigFromSettings()
```plantuml
@startuml
start
:set retraction_config;
:set config;
:set switch_retraction_config;
:set wipe_config;
stop
@endpuml
```
# processStartingCode()
```plantuml
@startuml
|#lightgray|GCodeExport|
|#pink|FffGcodeWriter|
start
|SliceDataStorage|
:getExtrudersUsed();
|Communication|
:isSequential();
|#pink|FffGcodeWriter|
if (is sequential) then (true)
    |#lightgray|GCodeExport|
    :getFileHeader();
endif
|#lightgray|GCodeExport|
:writeComment(Generated with Cura_SteamEngine);
|#pink|FffGcodeWriter|

if (flavor is GRIFFIN) then (true)
    :set tmp = T start_extruder_nr;
    note left
    GCode specific
    knowledge
    endnote
    |#lightgray|GCodeExport|
    :writeLine(tmp);
else (false)
    |#pink|FffGcodeWriter|
    #palegreen:processInitialLayerTemperature();
endif
|#lightgray|GCodeExport|
:writeExtrusionMode(false);
:writeCode(machine_start_gcode);
|#pink|FffGcodeWriter|
if (machine_extruders_share_nozzle) then (true)
    repeat
        |#lightgray|GCodeExport|
        :resetExtruderToPrimed();
        |#pink|FffGcodeWriter|
    repeat while (more extruder train) is (true)
endif

if (machine_heated_build_volume) then (true)
    |#lightgray|GCodeExport|
    :writeBuildVolumeTemperatureCommand ();
    |#pink|FffGcodeWriter|
endif
stop
@enduml
```

# processInitialLayerTemperature()
```plantuml
@startuml
start

stop
@enduml
```

# processNextMeshGroupCode()
```plantuml
@startuml
start

stop
@enduml
```

# setInfillAndSkinAngles()
```plantuml
@startuml
start

stop
@enduml
```

# setSupportAngles()
```plantuml
@startuml
start

stop
@enduml
```

# calculateMeshOrder()
```plantuml
@startuml
start

stop
@enduml
```

# calculateExtruderOrderPerLayer()
```plantuml
@startuml
start

stop
@enduml
```

# calculatePrimeLayerPerExtruder()
```plantuml
@startuml
start

stop
@enduml
```

# findLayerSeamsForSpiralize()
```plantuml
@startuml
start

stop
@enduml
```

# processRaft()
```plantuml
@startuml
start

stop
@enduml
```

# run_multiple_producers_ordered_consumer()
```plantuml
@startuml
|#pink|FffGcodeWriter|
start
    fork
        |LayerPlanBuffer|
        :handle(0);
        |#pink|FffGcodeWriter|
        
    fork again
        |LayerPlanBuffer|
        :handle(1);
        |#pink|FffGcodeWriter|
        
    fork again 
        |LayerPlanBuffer|
        :handle(n);
        |#pink|FffGcodeWriter|

     endfork
stop
@enduml
```

## handle()
```plantuml
@startuml
|LayerPlan|
start
|LayerPlanBuffer|
            :processBuffer();

|LayerPlan|
    :writeGCode(gcode);
     note left
        This also writes to a lot to GCodeExport
     endnote
|LayerPlanBuffer|
stop
@enduml
```

### processBuffer()

```plantuml
@startuml
|LayerPlanBuffer|
start
    :processFanSpeedLayerTime();
    :addConnectingTravelMove();
    :insertTempCommands();
    |Communication|
        :flushGCode();
    |LayerPlanBuffer|
stop
@enduml
```