function v = helics_filter_type_random_delay()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = helicsMEX(0, 1464812702);
  end
  v = vInitialized;
end
