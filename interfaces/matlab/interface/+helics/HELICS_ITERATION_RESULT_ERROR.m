function v = HELICS_ITERATION_RESULT_ERROR()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = helicsMEX(0, 131);
  end
  v = vInitialized;
end
