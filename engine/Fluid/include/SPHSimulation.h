#pragma once

#include <Simulation.h>

class SPHSimulation : public Simulation
  {
  public:
    
  protected:
    virtual void _PreProcessing() override;
    virtual void _Update() override;
    virtual void _PostProcessing() override;
  private:
  };