import type { GateModalType } from "../../types/types"

export function GateModal({ show, onClose, gates }: GateModalType) {

  if (!show) {
    return;
  }
  return (
    <>
      <p>Hello</p>
      <p>{gates?.gate_id}</p>
      <button onClick={onClose}>Close</button>
    </>
  )
}