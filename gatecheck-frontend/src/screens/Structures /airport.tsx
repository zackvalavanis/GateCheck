import { useEffect, useState } from "react"
import type { Gate } from "../../types/types"
import './airport.css'

export function Airport() {
  const [gates, setGates] = useState<Gate[]>([])
  const [gate, setGate] = useState("")

  useEffect(() => {
    const get_flights = async () => {
      try {
        const res = await fetch("/api/state")
        if (!res.ok) {
          console.log("No response");
          return;
        }
        const data = await res.json()
        setGates(data);
      } catch (error) {
        console.log(error);
      }
    }
    get_flights();

    const id = setInterval(async () => {
      const res2 = await fetch("/api/next", {
        "method": "POST"
      })
      const data = await res2.json();
      if (!res2.ok) {
        console.log("No response")
        return;
      } else {
        get_flights();
      }
      if (data.done) {
        clearInterval(id);
        return;
      }
    }, 5000)
    return () => clearInterval(id);
  }, [])

  const format_time = (minutes: number): string => {
    const hours = Math.floor(minutes / 60);
    const mins = minutes % 60;
    return `${String(hours).padStart(2, '0')}:${String(mins).padStart(2, '0')}`
  }

  const flights = gates.flatMap((g) => (
    g.flights
  ))

  const filteredFlights = flights.filter((flight) => {
    if (gate === "All" || gate == "") {
      return true
    }
    return flight.gate_id === gate
  });

  return (
    <div className='airportpage-layout'>
      <select value={gate} onChange={(e) => setGate(e.target.value)}>
        <option value="All">All</option>
        {gates.map((gate) => (
          <option key={gate.gate_id} value={gate.gate_id}>{gate.gate_id}</option>
        ))}
      </select>

      <div className="airport">
        <div>
          <table className="airport-table">
            <thead>
              <tr>
                <th>Airport</th>
                <th>Gate</th>
                <th>Flight</th>
                <th>Arrival Time</th>
                <th>Departure Time</th>
              </tr>
            </thead>
            <tbody>
              {filteredFlights.map((flight) => (
                <tr key={flight.flight}>
                  <td>{flight.airport}</td>
                  <td>{flight.gate_id}</td>
                  <td>{flight.flight}</td>
                  <td>{format_time(flight.low)}</td>
                  <td>{format_time(flight.high)}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  )
}