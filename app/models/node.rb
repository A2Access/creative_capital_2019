class Node < ApplicationRecord
  validates :device_id, numericality: { greater_than_or_equal_to: 1 }
end
