class Node < ApplicationRecord
  has_many :values, class_name: 'NodeValue'

  validates :device_id, numericality: { greater_than_or_equal_to: 1 }, uniqueness: true
end
