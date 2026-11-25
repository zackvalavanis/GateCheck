export function AirportSum() {

  const airports = [
    { airport_name: "O'hare", airport_id: "ORD" }
  ]



  return (
    <div>
      <select>
        {airports.map((airport) => (
          airport.airport_id
        ))}
      </select>
    </div>
  )
}