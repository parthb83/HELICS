function v = HELICS_FLAG_FORWARD_COMPUTE()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = helicsMEX(0, 37);
  end
  v = vInitialized;
end
