

export interface Flights {
  low: number
  high: number
  airport: string
  flight: string
  gate_id: string
}

export interface Gate {
  gate_id: string
  flights: Flights[]
}

export interface Airport {
  airport_name: string
  airport_id: string
}

export interface GateModalType {
  show: boolean
  onClose: () => void
  gates: Gate | null
  // flights: Flights[]
}
