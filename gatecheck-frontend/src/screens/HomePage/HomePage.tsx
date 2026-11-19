import type { Flights } from "../../types/types"
import { useState } from "react"


export function HomePage() {
  const [flights, setFlights] = useState<Flights[]>([])

  useState(() => {
    const get_flights = async () => {
      try {
        const res = await fetch("/")
        if (!res.ok) {
          console.log("No response");
        }
      } catch (error) {
        console.log(error);
      }
    }
    get_flights();
  }, [])


  return (
    <div>
      <h1>Home</h1>
    </div>
  )
}