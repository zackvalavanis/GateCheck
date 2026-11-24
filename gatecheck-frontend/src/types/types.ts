

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