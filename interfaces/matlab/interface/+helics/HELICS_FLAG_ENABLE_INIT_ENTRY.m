function v = HELICS_FLAG_ENABLE_INIT_ENTRY()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = helicsMEX(0, 46);
  end
  v = vInitialized;
end
