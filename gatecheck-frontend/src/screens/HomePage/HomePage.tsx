import type { Flights } from "../../types/types"
import { useEffect, useState } from "react"


export function HomePage() {
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
    <div>
      <h1>Home</h1>
      <div>
        <h1>Gates</h1>
        <h1></h1>
      </div>
      {flights.map((flight) => (
        <div key={flight.gate_id}>
          <h1>Gate: {flight.gate_id} Flight #:{flight.flight} Arrival: {format_time(flight.low)} Departure {format_time(flight.high)}</h1>
        </div>
      ))}
    </div>
  )
}