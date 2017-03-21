-- REGISTER vespa-hadoop.jar  -- Not needed in tests

-- Define short name for VespaStorage
DEFINE VespaStorage com.yahoo.vespa.hadoop.pig.VespaStorage();

-- Load data - one column for json data
metrics = LOAD 'src/test/resources/visit_data.json' AS (data:chararray);

-- Store into Vespa
STORE metrics INTO '$ENDPOINT' USING VespaStorage();
