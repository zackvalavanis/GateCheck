import { useState } from 'react'
import './airportsim.css'
import type { Airport } from '../../types/types'

export function AirportSim() {
  const [airport, setAirport] = useState<Airport | null>(null)

  const airports = [
    { airport_name: "Chicago O'Hare International Airport ", airport_id: "ORD" },
    { airport_name: "Chicago Midway International Airport", airport_id: "MDW" },
    { airport_name: "Hartsfield-Jackson Atlanta International Airport ", airport_id: "ATL" },
    { airport_name: "Dallas/Fort Worth International Airport ", airport_id: "DFW" },
    { airport_name: "Denver International Airport", airport_id: "DEN" },
    { airport_name: "Los Angeles International Airport ", airport_id: "LAX" },
  ]

  console.log("hello")


  return (
    <div className="airport-sim-page">
      <select value={airport?.airport_id ?? ""} onChange={(e) => setAirport(airports.find((port) => port.airport_id === e.target.value) ?? null)}>
        <option value="" />
        {airports.map((air) => (
          <option key={air.airport_id} value={air.airport_id}>{air.airport_id}</option>
        ))}
      </select>
    </div>
  )
}