import type { Flights } from "../../types/types"
import { useEffect, useState } from "react"
import './airport.css'

export function Airport() {
  const [flights, setFlights] = useState<Flights[]>([])

  useEffect(() => {
    const get_flights = async () => {
      try {
        const res = await fetch("/api/all_intervals")
        if (!res.ok) {
          console.log("No response");
        }
        const data = await res.json()
        setFlights(data);
      } catch (error) {
        console.log(error);
      }
    }
    get_flights();
  }, [])

  const format_time = (minutes: number): string => {
    const hours = Math.floor(minutes / 60);
    const mins = minutes % 60;
    return `${String(hours).padStart(2, '0')}: ${String(mins).padStart(2, '0')}`
  }


  return (
    <div className="airport">
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
          {flights.map((flight) => (
            <tr>
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
  )
}